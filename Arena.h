//
//  Arena.h
//  Game
//
//  Created by Florian D Dutronc on 5/26/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__Arena__
#define __Game__Arena__
#define TIXML_USE_STL

#include <stdio.h>
#include <string>
#include <vector>

#include "tinyxml2.h"

#include "Deadzone.h"

class Arena
{
public:
    Arena();
    ~Arena();
    
    std::string getBackground();
    std::vector<Coordinate> getWaypoints();
    std::vector<Deadzone> getDeadzones();
    bool createArenaFromFile(const char* arenaName);
    
private:
    
    int m_maxNumOfPlayers;
    int m_with;
    int m_height;
    
    std::string m_background;
    
    std::vector<Coordinate> m_waypoints;
    std::vector<Deadzone> m_deadzones;
};

#endif /* defined(__Game__Arena__) */
