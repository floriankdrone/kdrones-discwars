//
//  Deadzone.h
//  Game
//
//  Created by Florian D Dutronc on 5/26/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef Game_Deadzone_h
#define Game_Deadzone_h

typedef std::pair<int,int> Coordinate;

class Deadzone
{
public:

    Deadzone(int x, int y, int width, int height)
    {
        m_startingPoint.first = x;
        m_startingPoint.second = y;
        m_width = width;
        m_height = height;
    }
    
private:
    Coordinate m_startingPoint;
    int m_width;
    int m_height;
};

#endif
