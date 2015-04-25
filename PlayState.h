//
//  PlayState.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__PlayState__
#define __Game__PlayState__

#include <stdio.h>
#include <vector>

#include "GameState.h"

class GameObject;

class PlayState : public GameState
{
public:
    PlayState(){}
    ~PlayState(){}
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
private:
    
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__Game__PlayState__) */
