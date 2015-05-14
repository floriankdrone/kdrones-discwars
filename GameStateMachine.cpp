//
//  GameStateMachine.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <iostream>

#include "GameStateMachine.h"

GameStateMachine::GameStateMachine()
{}

GameStateMachine::~GameStateMachine()
{}

void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState)
{
    if (!m_gameStates.empty()) {
        std::cout << "Change State from " << m_gameStates.back()->getStateID() << " to " << pState->getStateID() << std::endl;
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }
        
        if (m_gameStates.back()->onExit()) {
            m_gameStates.pop_back();
        }
    }
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
    std::cout << "Current State is now " << m_gameStates.back()->getStateID() << std::endl;
}

void GameStateMachine::popState()
{
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->onExit()) {
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->update();
    } else {
        std::cout << "No more game states " << std::endl;
    }
}

void GameStateMachine::render()
{
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
}