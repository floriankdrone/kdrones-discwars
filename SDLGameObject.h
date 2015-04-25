//
//  SDLGameObject.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__SDLGameObject__
#define __Game__SDLGameObject__

#include <stdio.h>

#include "GameObject.h"
#include "TextureManager.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    
    SDLGameObject(const LoaderParams* pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    Vector2D& getPosition() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    
protected:
    
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    
    int m_width;
    int m_height;
    
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    
    std::string m_textureID;
};

#endif /* defined(__Game__SDLGameObject__) */
