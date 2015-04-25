//
//  PauseState.h
//  Game
//
//  Created by Florian D Dutronc on 4/16/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__PauseState__
#define __Game__PauseState__

#include <vector>

#include "GameState.h"
#include "GameObject.h"

class PauseState : public GameState
{
public:
    PauseState(){}
    ~PauseState(){}
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_menuID; }
    
private:
    static void s_pauseToPlay();
    static void s_exitToMenu();
    static void s_exitGame();
    
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};


#endif /* defined(__Game__PauseState__) */
