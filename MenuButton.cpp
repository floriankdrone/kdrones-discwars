//
//  MenuButton.cpp
//  Game
//
//  Created by Florian D Dutronc on 3/30/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <iostream>

#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (*callback)()) : SDLGameObject(pParams),
    m_callback(callback)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D* pMousePos =TheInputHandler::Instance()->getMousePosition();
    if (pMousePos->getX() < (m_position.getX() + m_width)
        && pMousePos->getX() > m_position.getX()
        && pMousePos->getY() < (m_position.getY()) + m_height
        && pMousePos->getY() > m_position.getY()) {
        m_currentFrame = MOUSE_OVER;
        
        if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
            //std::cout << "Mouse clicked" << std::endl;
            m_currentFrame = CLICKED;
            m_bReleased = false;
        }
        else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && !m_bReleased)
        {
            //std::cout << "Mouse was released." << std::endl;
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
            m_callback();
        }
        else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            //std::cout << "Mouse over" << std::endl;
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_bReleased = true;
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}