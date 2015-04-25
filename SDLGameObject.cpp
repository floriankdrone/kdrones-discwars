//
//  SDLGameObject.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include "SDLGameObject.h"

#include <iostream>

#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
: GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    
    m_currentRow = 1;
    m_currentFrame = 1;
    m_velocity.setX(0);
    m_velocity.setY(0);
    
    std::cout << "Created at position " << m_position.getX() << " || " << m_position.getY() << std::endl;
}

void SDLGameObject::draw()
{
    if (m_velocity.getX() < 0) {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    }
    else
    {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
    }
    
}

void SDLGameObject::clean()
{
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}