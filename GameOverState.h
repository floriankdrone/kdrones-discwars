//
//  GameOverState.h
//  Game
//
//  Created by Florian D Dutronc on 4/25/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__GameOverState__
#define __Game__GameOverState__

#include <stdio.h>
#include <vector>

#include "GameState.h"

class GameObject;

class GameOverState : public GameState
{
public:
    
    GameOverState(std::string endString){ m_endString = endString; }
    ~GameOverState(){}
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_gameOverID; }

private:
    
    std::string m_endString;
    
    static void s_gameOverToMain();
    static void s_restartToPlay();
    
    static const std::string s_gameOverID;
    
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__Game__GameOverState__) */
