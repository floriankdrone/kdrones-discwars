//
//  Disc.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <iostream>

#include "Disc.h"

#include "Game.h"
#include "InputHandler.h"

#include <SDL2_mixer/SDL_mixer.h>

#define LENGTH 7

enum window_sides
{
    LEFT_SIDE = 0,
    RIGHT_SIDE = 1,
    TOP_SIDE = 2,
    BOTTOM_SIDE = 3
};

Disc::Disc(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    std::cout << "Disc created" << std::endl;
    m_velocity.setX(0);
    m_velocity.setY(0);
    m_currentFrame = 0;
    m_position.setX(0);
    m_position.setY(0);
    m_isReturning = false;
    m_angle = 0;
    resetBounceCount();
    m_shouldReturnToPlayer = false;
    m_damage = 10;
}

Disc::~Disc()
{
    std::cout << "Disc destructed" << std::endl;
}

void Disc::draw()
{
    if (m_angle >= 360) {
        m_angle = 0;
    } else {
        m_angle += 5;
    }
    TextureManager::Instance()->drawRotatingFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, m_angle, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
}

void Disc::update()
{
    if (m_position.getX() < 0)
    {
        bounce(LEFT_SIDE);
    }
    else if (m_position.getX() + m_width > TheGame::Instance()->getWindowWidth())
    {
        bounce(RIGHT_SIDE);
    }
    else if (m_position.getY() < 0)
    {
        bounce(TOP_SIDE);
    }
    else if (m_position.getY()+m_height > TheGame::Instance()->getWindowHeight())
    {
        bounce(BOTTOM_SIDE);
    }
    SDLGameObject::update();
}
void Disc::clean()
{
    SDLGameObject::clean();
}

void Disc::justThrown(Vector2D& startingPosition, int type)
{
    m_position = startingPosition;
    
    switch (type) {
        case 0:
        {
            Vector2D* target = TheInputHandler::Instance()->getMousePosition();
            
            m_velocity = *target - m_position;
            setDirection(m_velocity.getX(), m_velocity.getY());
            break;
        }
        
        case 1:
        {
            setDirection(TheInputHandler::Instance()->xvalue(0, 2), TheInputHandler::Instance()->yvalue(0, 2));
        }
            
        default:
            break;
    }
}

void Disc::returnToPlayer(Vector2D& endingPosition)
{
    m_velocity = endingPosition - m_position;
    
    setDirection(m_velocity.getX(), m_velocity.getY());
}

void Disc::caughtBack()
{
    std::cout << "Disc caught back" << std::endl;
    m_velocity.setX(0);
    m_velocity.setY(0);
    m_shouldReturnToPlayer = false;
    resetBounceCount();
}

void Disc::bounce(int windowSide)
{
    std::cout << "disc bounced, bounce = " << m_bounce << std::endl;
    switch (windowSide) {
        case LEFT_SIDE:
            std::cout << "LEFT_SIDE" << std::endl;
            m_velocity.setX(-(m_velocity.getX()));
            break;
        case RIGHT_SIDE:
            std::cout << "RIGHT_SIDE" << std::endl;
            m_velocity.setX(-(m_velocity.getX()));
            break;
        case TOP_SIDE:
            std::cout << "TOP_SIDE" << std::endl;
            m_velocity.setY(-(m_velocity.getY()));
            break;
        case BOTTOM_SIDE:
            std::cout << "BOTTOM_SIDE" << std::endl;
            m_velocity.setY(-(m_velocity.getY()));
        default:
            break;
    }
    m_bounce += 1;
}

void Disc::resetBounceCount()
{
    std::cout << "resetBounceCount" << std::endl;
    m_bounce = 0;
}

void Disc::setDirection(float adjacentSide, float oppositeSide)
{
    float radian = atan2(oppositeSide, adjacentSide);
    m_velocity.setX(cosf(radian) * LENGTH);
    m_velocity.setY(sinf(radian) * LENGTH);
}