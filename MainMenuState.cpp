//
//  MainMenuState.cpp
//  Game
//
//  Created by Florian D Dutronc on 3/30/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include "MainMenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

class Game;

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/1PlayerPlayButtons.png", "1playerplaybutton", TheGame::Instance()->getRenderer())) {
        std::cout << "Issue with /Users/floriandutronc/Desktop/Game/Game/assets/1PlayerPlayButtons.png does not exist" << std::endl;
        return false;
    }
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/2PlayersPlayButtons.png", "2playersplaybutton", TheGame::Instance()->getRenderer())) {
        std::cout << "Issue with /Users/floriandutronc/Desktop/Game/Game/assets/2PlayersPlayButtons.png does not exist" << std::endl;
        return false;
    }
    if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/Game/Game/assets/ExitButtons.png", "exitbutton", TheGame::Instance()->getRenderer())) {
        std::cout << "Issue with /Users/floriandutronc/Desktop/Game/Game/assets/ExitButtons.png does not exist" << std::endl;
        return false;
    }
    
    GameObject* button1 = new MenuButton(new LoaderParams(250, 75, 150, 75, "1playerplaybutton"), s_menuToPlay);
    GameObject* button2 = new MenuButton(new LoaderParams(250, 150, 150, 75, "2playersplaybutton"), s_menuToPlay);
    GameObject* button3 = new MenuButton(new LoaderParams(250, 225, 150, 75, "exitbutton"), s_exitFromMenu);
    
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    m_gameObjects.push_back(button3);
    
    std::cout << "entering Menustate" << std::endl;
    return true;
}

bool MainMenuState::onExit()
{
    std::cout << "onExit MainMenu with gameObject size:" << m_gameObjects.size() << std::endl;
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    std::cout << "gameObject cleared so size:" << m_gameObjects.size() << std::endl;
    TheTextureManager::Instance()->clearFromTextureMap("1playerplaybutton");
    TheTextureManager::Instance()->clearFromTextureMap("2playersplaybutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
    std::cout << "exiting Menustate" << std::endl;
    return true;
}

void MainMenuState::s_menuToPlay()
{
    std::cout << "Play button clicked" << std::endl;
    TheGame::Instance()->getStateMachine()->changeState(new PlayState(1));
}

void MainMenuState::s_exitFromMenu()
{
    std::cout << "Exit From Menu" << std::endl;
    TheGame::Instance()->quit();
}