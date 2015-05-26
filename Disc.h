//
//  Disc.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__Disc__
#define __Game__Disc__

#include <stdio.h>

#include "SDLGameObject.h"

#define BOUNCE_NUM 3

class Disc : public SDLGameObject
{
public:
    
    Disc(const LoaderParams* pParams);
    ~Disc();
    
    void draw();
    void update();
    void clean();
    
    void justThrown(Vector2D& position, int type);
    void bounce(int windowSide);
    void returnToPlayer(Vector2D& position);
    bool shouldReturnToPlayer() { return m_shouldReturnToPlayer; }
    void shouldReturnToPlayer(bool b) { m_shouldReturnToPlayer = b; }
    
    void caughtBack();
    int getBounceCount()
    {
        return m_bounce;
    }
private:
    void resetBounceCount();
    void setDirection(float x, float y);
    
    bool m_isThrown;
    bool m_isReturning;
    int m_bounce;
    double m_angle;
    bool m_shouldReturnToPlayer;
    
    int m_damage;
    
};

#endif /* defined(__Game__Disc__) */
