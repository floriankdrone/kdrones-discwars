//
//  Deadzone.cpp
//  Game
//
//  Created by Florian D Dutronc on 5/27/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <stdio.h>

#include "Deadzone.h"

Deadzone::Deadzone(Coordinate startingpoint, int width, int height)
{
    m_startingPoint = startingpoint;
    m_width = width;
    m_height = height;
}

Deadzone::~Deadzone()
{
}

Coordinate Deadzone::getCoordinate()
{
    return m_startingPoint;
}

int Deadzone::getHeight()
{
    return m_height;
}

int Deadzone::getWidth()
{
    return m_width;
}

