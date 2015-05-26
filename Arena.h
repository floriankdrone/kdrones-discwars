//
//  Arena.h
//  Game
//
//  Created by Florian D Dutronc on 5/26/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__Arena__
#define __Game__Arena__

#include <stdio.h>
#include <vector>

#include "tinyxml.h"

#include "Deadzone.h"

class Arena
{
public:
    Arena();
    ~Arena();
    
private:
    bool createArenaFromFile(const std::string arenaID);
    
    int m_maxNumOfPlayers;
    int m_with;
    int m_height;
    
    std::vector<Coordinate> waypoints;
    std::vector<Deadzone> deadzones;
};

#endif /* defined(__Game__Arena__) */
