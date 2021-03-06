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
#include "Arena.h"

#include "Player.h"

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
    
    bool setupFor1Player(std::vector<Coordinate> waypoints);
    bool setupFor2Players(std::vector<Coordinate> waypoints);
    
    int m_numOfPlayers;
    Arena* m_arena;
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__Game__PlayState__) */
