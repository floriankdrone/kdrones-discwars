//
//  Game.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__Game__
#define __Game__Game__

#include <stdio.h>
#include <vector>

#include "TextureManager.h"
#include "SDLGameObject.h"
#include "Player.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "GameStateMachine.h"

class Game
{
public:
    
    static Game* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void render();
    void update();
    void handleEvents();
    void clean();
    
    bool running() { return m_bRunning; }
    
    void quit() { m_bRunning = false; }
    
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    GameStateMachine* getStateMachine() const { return m_pGameStateMachine; }
    
    int getWindowWidth() { return m_width; }
    int getWindowHeight() { return m_height; }
    
    bool positionIsInGameWindow(int x, int y)
    {
        if (x < 0 || x > m_width || y < 0 || y > m_height) {
            return false;
        }
        return true;
    }
    
private:
    
    Game() {}
    
    static Game* s_pInstance;
    
    int m_width;
    int m_height;
    bool m_bRunning;
    
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    std::vector<GameObject*> m_gameObjects;
    
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;
#endif /* defined(__Game__Game__) */
