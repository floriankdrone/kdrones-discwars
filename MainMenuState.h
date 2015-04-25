//
//  MainMenuState.h
//  Game
//
//  Created by Florian D Dutronc on 3/30/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__MainMenuState__
#define __Game__MainMenuState__

#include <stdio.h>
#include <vector>
#include <iostream>

#include "GameState.h"
#include "GameObject.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(){}
    ~MainMenuState(){}
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_menuID; }

private:
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__Game__MainMenuState__) */
