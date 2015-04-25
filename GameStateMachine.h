//
//  GameStateMachine.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__GameStateMachine__
#define __Game__GameStateMachine__

#include <stdio.h>
#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
    GameStateMachine();
    ~GameStateMachine();
    
    
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    
    void update();
    void render();
    
private:
    
    std::vector<GameState *> m_gameStates;
};

#endif /* defined(__Game__GameStateMachine__) */
