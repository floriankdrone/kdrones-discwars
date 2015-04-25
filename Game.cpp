//
//  Game.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include <iostream>

#include "Game.h"

#include "PlayState.h"
#include "MainMenuState.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        std::cout << "SDL init success" << std::endl;
        
        m_width = width;
        m_height = height;
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if (m_pWindow != 0)
        {
            std::cout << "window creation success" << std::endl;
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0)
            {
                std::cout << "renderer creation success" << std::endl;
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

                TheInputHandler::Instance()->initialiseController();
                
                m_pGameStateMachine = new GameStateMachine();
                m_pGameStateMachine->changeState(new MainMenuState());
                // m_pGameStateMachine->changeState(new PlayState());
                
            }
            else
            {
                std::cout << "renderer init fail" << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "window init fail" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "sdl init fail" << std::endl;
        return false;  // sdl could not initialize
    }
    std::cout << "Init success" << std::endl;
    m_bRunning = true;
    
    return true;
}

void Game::render()
{
    // clear the render to the draw color
    SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();
    
    // show window
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
    std::cout << "Cleaning game" << std::endl;
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::update()
{
    m_pGameStateMachine->update();
}
