//
//  MenuButton.h
//  Game
//
//  Created by Florian D Dutronc on 3/30/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__MenuButton__
#define __Game__MenuButton__

#include <stdio.h>
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
    
    MenuButton(const LoaderParams* pParams, void (*m_callback)());
    
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    void (*m_callback)();
    
    
    
    bool m_bReleased;
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };
};
#endif /* defined(__Game__MenuButton__) */
