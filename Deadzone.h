//
//  Deadzone.h
//  Game
//
//  Created by Florian D Dutronc on 5/26/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef Game_Deadzone_h
#define Game_Deadzone_h

#include <utility>

typedef std::pair<int,int> Coordinate;

class Deadzone
{
public:
    
    Deadzone(Coordinate startingpoint, int width, int height);
    ~Deadzone();
    
    Coordinate getCoordinate();
    int getWidth();
    int getHeight();
    
private:
    Coordinate m_startingPoint;
    int m_width;
    int m_height;
};

#endif
