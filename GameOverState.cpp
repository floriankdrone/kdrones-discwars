//
//  GameOverState.cpp
//  Game
//
//  Created by Florian D Dutronc on 4/25/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include "GameOverState.h"

#include "MainMenuState.h"
#include "PlayState.h"

#include "Game.h"
#include "MenuButton.h"
#include "TextureManager.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartToPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState(2));
}

bool GameOverState::onEnter()
{
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    
    GameObject* button1 = new MenuButton(new LoaderParams(250, 100, 200, 80, "mainbutton"), s_gameOverToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(250, 200, 200, 80, "restartbutton"), s_restartToPlay);
    
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    
    std::cout << "entering GameOver State" << std::endl;
    
    return true;
}

bool GameOverState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    std::cout << "gameObject cleared so size:" << m_gameObjects.size() << std::endl;
    TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
    TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
    return true;
}

void GameOverState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

void GameOverState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}