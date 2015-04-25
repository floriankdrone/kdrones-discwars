//
//  InputHandler.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "InputHandler.h"
#include "Game.h"

TheInputHandler* InputHandler::s_pInstance = 0;

void InputHandler::initialiseController()
{
    for (int k = 0; k < 3; k++) {
        m_mouseButtonStates.push_back(false);
    }
    
    m_mousePosition = new Vector2D(0,0);
}

void InputHandler::update()
{
    m_mouseReleased = false;
    m_keystate = SDL_GetKeyboardState(0);
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_QUIT:
                TheGame::Instance()->quit();
                break;
                
            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
                
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                m_mouseReleased = true;
                break;
            case SDL_KEYDOWN:
                onKeyDown();
                break;
            case SDL_KEYUP:
                onKeyUp();
                break;
                
            default:
                break;
        }
    }
}

void InputHandler::clean()
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[MIDDLE] = false;
    m_mouseButtonStates[RIGHT] = false;
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = false;
        
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onKeyDown()
{
}

void InputHandler::onKeyUp()
{
}