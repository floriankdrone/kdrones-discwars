//
//  GameState.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef Game_GameState_h
#define Game_GameState_h

#include <string>

class GameState
{
public:
    
    virtual ~GameState(){}
    
    virtual void update() = 0;
    virtual void render() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual std::string getStateID() const = 0;
};

#endif
