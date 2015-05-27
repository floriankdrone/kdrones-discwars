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

#include <sstream>

#include "Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
        
        if (outOfBounds(dynamic_cast<SDLGameObject*>(m_gameObjects[i]))) {
            TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
        }
    }

    if (m_numOfPlayers == 1) {
        Player* p = dynamic_cast<Player*>(m_gameObjects[0]);
        if (checkCollision(p, dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
        {
        std::cout << p->getName() << " WINS!" << std::endl;
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
        }
    }
    else
    {
        for (int i = 0 ; i < m_numOfPlayers; i++) {
            Player* p = dynamic_cast<Player*>(m_gameObjects[i]);
            for (int j =0 ; j < m_numOfPlayers; j++) {
                if (j == i) {
                    continue;
                }
                Player* p2 = dynamic_cast<Player*>(m_gameObjects[j]);
                if (checkCollision(p, p2))
                {
                    std::cout << p2->getName() << " Got Killed!" << std::endl;
                    std::cout << p->getName() << " WINS!" << std::endl;
                    TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
                }
            }
        }
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
    m_arena = new Arena();
    m_arena->createArenaFromFile("default");
    
    if (!TheTextureManager::Instance()->load(m_arena->getBackground(), "background", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    std::vector<Coordinate> waypoints = m_arena->getWaypoints();
    
    if (waypoints.size() < m_numOfPlayers || waypoints.size() < 2) {
        std::cout << "Cannot initialise the game since there are not enough waypoints on the map for the number of players" << std::endl;
        return false;
    }
    
    switch (m_numOfPlayers) {
        case 1:
        {
            std::cout << "1 player game launched." << std::endl;
            if(!setupFor1Player(waypoints))
            {
                return false;
            }
            break;
        }
        case 2:
        {
            std::cout << "2 player game launched." << std::endl;
            if(!setupFor2Players(waypoints))
            {
                return false;
            }
        }
        default:
            break;
    }
    
    TheSoundManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/proceed.aiff", "transitionToGames", SOUND_SFX);
    
    TheSoundManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/Daft_Punk-Arena.wav", "gameSong", SOUND_MUSIC);
    
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
    switch (m_numOfPlayers) {
        case 1:
            TheTextureManager::Instance()->clearFromTextureMap("sampleEnemy");
            break;
        case 2:
            TheTextureManager::Instance()->clearFromTextureMap("player2");
        default:
            break;
    }
    delete m_arena;
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
    std::vector<Deadzone> deadzones = m_arena->getDeadzones();
    
    for (int i = 0; i < deadzones.size(); i++) {
        int left = deadzones[i].getCoordinate().first;
        int right = deadzones[i].getCoordinate().first + deadzones[i].getWidth();
        int top = deadzones[i].getCoordinate().second;
        int bot = deadzones[i].getCoordinate().second + deadzones[i].getHeight();
        
        if ((player->getPosition().getX() > left) && (player->getPosition().getX() < right) &&
            (player->getPosition().getY() > top) && (player->getPosition().getY() < bot)) {
            return true;
        }
    }
    
    return false;
}

bool PlayState::setupFor1Player(std::vector<Coordinate> waypoints)
{
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/tron_player_small.png", "player", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    GameObject* player = new Player(new LoaderParams(50, 200, 20, 71, "player"), KEYBOARD);
    
    m_gameObjects.push_back(player);
    
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/rider.png", "sampleEnemy", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    GameObject* sampleEnemy = new SampleEnemy(new LoaderParams(550, 200, 33, 44, "sampleEnemy"));
    m_gameObjects.push_back(sampleEnemy);
    return true;
}

bool PlayState::setupFor2Players(std::vector<Coordinate> waypoints)
{
    
    for (int i = 0 ; i < m_numOfPlayers; i++) {
        std::stringstream sstm;
        sstm << "player" << i;
        InputControllerType t;
        std::string s;
        if (i == 0) {
            t = KEYBOARD;
            s = "/Users/floriandutronc/Desktop/Game/Game/assets/tron_player_small.png";
        } else {
            t = CONTROLLER;
            s = "/Users/floriandutronc/Desktop/Game/Game/assets/tron_player_small_opposite.png";
        }
        if (!TheTextureManager::Instance()->load(s, sstm.str(), TheGame::Instance()->getRenderer())) {
            return false;
        }
        GameObject* player = new Player(new LoaderParams(waypoints[i].first, waypoints[i].second, 20, 71, sstm.str()), t);
        m_gameObjects.push_back(player);
    }
    return true;
}
