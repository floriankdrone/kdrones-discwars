//
//  Player.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__Player__
#define __Game__Player__

#include <stdio.h>

#include "SDLGameObject.h"
#include "Disc.h"

#define DISC_RAD 20

enum InputControllerType {
    KEYBOARD = 1,
    CONTROLLER = 2
};

class Player : public SDLGameObject
{
public:
    
    Player(const LoaderParams* pParams, InputControllerType inputControllerType);
    ~Player();
    
    void draw();
    void update();
    void clean();
    
    Disc* getMyDisc();
    
    std::string getName();
    
private:
    
    void handleInput();
    
    bool goRight();
    bool goLeft();
    bool goUp();
    bool goDown();
    
    bool throwDisc();
    bool discHasReturned();
    
    Disc* myDisc;
    bool hasDisc;
    
    std::string m_name;
    
    InputControllerType m_inputControllerType;
    
};

#endif /* defined(__Game__Player__) */
