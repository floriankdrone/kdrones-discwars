//
//  GameObject.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef Game_GameObject_h
#define Game_GameObject_h

#include "LoaderParams.h"

class GameObject
{
public:
    
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    
protected:
    
    GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}
};

#endif
