//
//  InputHandler.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__InputHandler__
#define __Game__InputHandler__

#include "SDL2/SDL.h"

#include <vector>

#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        
        return s_pInstance;
    }
    
    void update();
    
    void clean();
    
    void initialiseController();
    
    bool getMouseButtonState(int buttonNumber)
    {
        return m_mouseButtonStates[buttonNumber];
    }
    Vector2D* getMousePosition()
    {
        return m_mousePosition;
    }
    bool isMouseButtonReleased()
    {
        return m_mouseReleased;
    }
    
    bool isKeyDown(SDL_Scancode key)
    {
        if (m_keystate != 0) {
            if (m_keystate[key] == 1) {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }
    
    void reset();
    
private:
    
    InputHandler() {}
    ~InputHandler() {}
    
    void onKeyDown();
    void onKeyUp();
    
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    
    static InputHandler* s_pInstance;
    
    std::vector<std::vector<bool>> m_buttonStates;
    
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    bool m_mouseReleased;
    
    const Uint8* m_keystate;
};

typedef InputHandler TheInputHandler;

#endif /* defined(__Game__InputHandler__) */
