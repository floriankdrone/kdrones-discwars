//
//  PlayState.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <iostream>

#include "PlayState.h"

#include "GameOverState.h"

#include "Game.h"

#include <SDL2_mixer/SDL_mixer.h>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
        
        if (outOfBounds(dynamic_cast<SDLGameObject*>(m_gameObjects[i]))) {
            TheGame::Instance()->getStateMachine()->changeState(new GameOverState("player fell down!"));
        }
    }
    /*
    if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState("player 1 loses!"));
    }
    
    if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[1]), dynamic_cast<SDLGameObject*>(m_gameObjects[0]))) {
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState("player 2 loses!"));
    }*/
}

void PlayState::render()
{
    TheTextureManager::Instance()->draw("background", 0, 0, 700, 400, TheGame::Instance()->getRenderer());
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/play_background1.png", "background", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/SDLDevelopment/SDLDevelopment/SDLDevelopment/assets/tron_player_small.png", "player", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    GameObject* player = new Player(new LoaderParams(50, 200, 20, 71, "player"), 0, (TheGame::Instance()->getWindowWidth() / 2.5));
    
    m_gameObjects.push_back(player);
    
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
    
    Mix_Chunk* sound = Mix_LoadWAV("/Users/floriandutronc/Desktop/SDLDevelopment/SDLDevelopment/SDLDevelopment/assets/proceed.aiff");

    Mix_Chunk* song = Mix_LoadWAV("/Users/floriandutronc/Desktop/SDLDevelopment/SDLDevelopment/SDLDevelopment/assets/Daft_Punk-Arena.wav");
    
    if (song == 0 || sound == 0) {
        std::cout << "Could not load music - " << Mix_GetError() << std::endl;
        return false;
    } else {
        std::cout << "song loaded!" << std::endl;
    }
    
    Mix_PlayChannel(-1, song, -1);
    Mix_FadeInChannel(-1, sound, 0, 5000);
    std::cout << "Entering PlayState" << std::endl;
    
    return true;
}

bool PlayState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("player");
    std::cout << "Exiting PlayState" << std::endl;
    return true;
}

bool PlayState::checkCollision(SDLGameObject* player, SDLGameObject* player2)
{
    return false;
}

bool PlayState::outOfBounds(SDLGameObject* player)
{
    int right = TheGame::Instance()->getWindowWidth() / 1.5;
    int left = TheGame::Instance()->getWindowWidth() / 2.5;
    
    if (player->getPosition().getX() < left || player->getPosition().getX() > right) {
        return false;
    }
    
    return true;
}
