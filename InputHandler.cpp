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

void InputHandler::initialiseJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    if (SDL_NumJoysticks() > 0) {
        for (int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if (joy) {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
                
                std::vector<bool> tempButtons;
                
                for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
                    tempButtons.push_back(false);
                }
                
                m_buttonStates.push_back(tempButtons);
            }
            else
            {
                std::cout << SDL_GetError() << std::endl;
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised =true;
        
        std::cout << "Initialised " << m_joysticks.size() << " joystick(s)" << std::endl;
    }
    else
    {
        m_bJoysticksInitialised = false;
    }
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
            {
                TheGame::Instance()->quit();
                break;
            }
                
            case SDL_MOUSEMOTION:
            {
                onMouseMove(event);
                break;
            }
                
            case SDL_MOUSEBUTTONDOWN:
            {
                onMouseButtonDown(event);
                break;
            }
                
            case SDL_MOUSEBUTTONUP:
            {
                onMouseButtonUp(event);
                m_mouseReleased = true;
                break;
            }
                
            case SDL_KEYDOWN:
            {
                onKeyDown();
                break;
            }
                
            case SDL_KEYUP:
            {
                onKeyUp();
                break;
            }
                
            case SDL_JOYAXISMOTION:
            {
                int whichOne = event.jaxis.which;
                if (event.jaxis.axis == 0) {
                    if (event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].first->setX(1);
                    }
                    else if (event.jaxis.value < -m_joystickDeadZone)
                    {
                        m_joystickValues[whichOne].first->setX(-1);
                    }
                    else
                    {
                        m_joystickValues[whichOne].first->setX(0);
                    }
                }
                if (event.jaxis.axis == 1) {
                    if (event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].first->setY(1);
                    }
                    else if (event.jaxis.value < -m_joystickDeadZone)
                    {
                        m_joystickValues[whichOne].first->setY(-1);
                    }
                    else
                    {
                        m_joystickValues[whichOne].first->setY(0);
                    }
                }
                if (event.jaxis.axis == 2) {
                    std::cout << "moving x axis stick 2 value: " << event.jaxis.value << std::endl;
                    if (event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].second->setX(event.jaxis.value);
                    }
                    else if (event.jaxis.value < -m_joystickDeadZone)
                    {
                        m_joystickValues[whichOne].second->setX(event.jaxis.value);
                    }
                    else
                    {
                        m_joystickValues[whichOne].second->setX(0);
                    }
                }
                if (event.jaxis.axis == 5) {
                    if (event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].second->setY(event.jaxis.value);
                    }
                    else if (event.jaxis.value < -m_joystickDeadZone)
                    {
                        m_joystickValues[whichOne].second->setY(event.jaxis.value);
                    }
                    else
                    {
                        m_joystickValues[whichOne].second->setY(0);
                    }
                }
                break;
            }
                
            case SDL_JOYBUTTONDOWN:
            {
                int whichOne = event.jaxis.which;
                m_buttonStates[whichOne][event.jbutton.button] = true;
                break;
            }
                
            case SDL_JOYBUTTONUP:
            {
                int whichOne = event.jaxis.which;
                m_buttonStates[whichOne][event.jbutton.button] = false;
                break;
            }
                
            default:
            {
                break;
            }
        }
    }
}

void InputHandler::clean()
{
    if (m_bJoysticksInitialised) {
        for (unsigned int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
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

int InputHandler::xvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0) {
        if (stick == 1) {
            return m_joystickValues[joy].first->getX();
        }
        else if (stick == 2)
        {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0) {
        if (stick == 1) {
            return m_joystickValues[joy].first->getY();
        }
        else if (stick == 2)
        {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}
