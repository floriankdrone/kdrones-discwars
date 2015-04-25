//
//  Player.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__Player__
#define __Game__Player__

#include <stdio.h>

#include "SDLGameObject.h"
#include "Disc.h"

#define DISC_RAD 20

class Player : public SDLGameObject
{
public:
    
    Player(const LoaderParams* pParams, int zoneWidthStart, int zoneWidthEnd);
    ~Player();
    
    void draw();
    void update();
    void clean();
    
private:
    
    void handleInput();
    void dies();
    
    bool goRight();
    bool goLeft();
    bool goUp();
    bool goDown();
    int m_zoneWidthStart;
    int m_zoneWidthEnd;
    
    int m_health;
    
    bool throwDisc();
    bool discHasReturned();
    
    Disc* myDisc;
    bool hasDisc;
    
};

#endif /* defined(__Game__Player__) */
