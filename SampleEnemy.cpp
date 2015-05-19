//
//  SampleEnemy.cpp
//  Game
//
//  Created by Florian D Dutronc on 5/18/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include "SampleEnemy.h"

#include <iostream>

#include "Game.h"

SampleEnemy::SampleEnemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    std::cout << "SampleEnemy created" << std::endl;
    m_currentFrame = 0;
}

SampleEnemy::~SampleEnemy()
{
    std::cout << "SampleEnemy destructed" << std::endl;
}

void SampleEnemy::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SampleEnemy::update()
{
    SDLGameObject::update();
}

void SampleEnemy::clean()
{
    SDLGameObject::clean();
}
