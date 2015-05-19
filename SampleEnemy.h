//
//  SampleEnemy.h
//  Game
//
//  Created by Florian D Dutronc on 5/18/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__SampleEnemy__
#define __Game__SampleEnemy__

#include <stdio.h>

#include "SDLGameObject.h"
#include "Disc.h"

#define DISC_RAD 20

class SampleEnemy : public SDLGameObject
{
public:
    
    SampleEnemy(const LoaderParams* pParams);
    ~SampleEnemy();
    
    void draw();
    void update();
    void clean();
    
};


#endif /* defined(__Game__SampleEnemy__) */
