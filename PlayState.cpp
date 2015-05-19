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
#include "SampleEnemy.h"
#include "Disc.h"

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
    
    if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState("player 1 loses!"));
    }
    switch (m_numOfPlayers) {
        case 2:
            if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[1]), dynamic_cast<SDLGameObject*>(m_gameObjects[2]))) {
                TheGame::Instance()->getStateMachine()->changeState(new GameOverState("player 1 loses!"));
            }
            break;
            
        default:
            break;
    }
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
    
    switch (m_numOfPlayers) {
        case 1:
            setupFor1Player();
            break;
        case 2:
            setupFor2Players();
        default:
            break;
    }
    
    TheSoundManager::Instance()->load("/Users/floriandutronc/Desktop/SDLDevelopment/SDLDevelopment/SDLDevelopment/assets/proceed.aiff", "transitionToGames", SOUND_SFX);
    
    TheSoundManager::Instance()->load("/Users/floriandutronc/Desktop/SDLDevelopment/SDLDevelopment/SDLDevelopment/assets/Daft_Punk-Arena.wav", "gameSong", SOUND_MUSIC);
    
    TheSoundManager::Instance()->playSound("transitionToGames", 0);
    TheSoundManager::Instance()->playMusic("gameSong", -1);
    
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
    TheSoundManager::Instance()->stopMusic();
    std::cout << "Exiting PlayState" << std::endl;
    return true;
}

bool PlayState::checkCollision(SDLGameObject* player, SDLGameObject* player2)
{
    Disc* disc = dynamic_cast<Player*>(player)->getMyDisc();
    if (disc->getPosition().getX() + disc->getWidth() >= player2->getPosition().getX()
        && disc->getPosition().getX() <= player2->getPosition().getX() + player2->getWidth()
        && disc->getPosition().getY() + disc->getHeight() >= player2->getPosition().getY()
        && disc->getPosition().getY() <= player2->getPosition().getY() + player2->getHeight()) {
        std::cout << "collsion detected" << std::endl;
        return true;
    }
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

void PlayState::setupFor1Player()
{
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/rider.png", "sampleEnemy", TheGame::Instance()->getRenderer())) {
        std::cout << "sample enemy was not found." << std::endl;
    }
    
    GameObject* sampleEnemy = new SampleEnemy(new LoaderParams(550, 150, 33, 44, "sampleEnemy"));
    m_gameObjects.push_back(sampleEnemy);
}

void PlayState::setupFor2Players()
{
}
