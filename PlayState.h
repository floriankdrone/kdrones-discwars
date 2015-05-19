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

#include "SDLGameObject.h"

class GameObject;

class PlayState : public GameState
{
public:
    PlayState(int numOfPlayers){ m_numOfPlayers = numOfPlayers; }
    ~PlayState(){}
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
    bool checkCollision(SDLGameObject* player, SDLGameObject* player2);
    bool outOfBounds(SDLGameObject* player);
    
private:
    
    void setupFor1Player();
    void setupFor2Players();
    
    int m_numOfPlayers;
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__Game__PlayState__) */
