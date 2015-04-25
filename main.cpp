//
//  main.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <iostream>

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, const char * argv[]) {
    Uint32 frameStart, frameTime;
    
    std::cout << "game init attempt..." << std::endl;
    
    if (TheGame::Instance()->init("Disc Wars", 100, 100, 700, 400, 0)) {
        std::cout << "game init success!" << std::endl;
        
        while (TheGame::Instance()->running())
        {
            frameStart = SDL_GetTicks();
            
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            
            frameTime = SDL_GetTicks() - frameStart;
            
            if (frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << std::endl;
        return -1;
    }
    
    std::cout << "game closing..." << std::endl;
    TheGame::Instance()->clean();
    
    return 0;
}

