//
//  TextureManager.h
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__TextureManager__
#define __Game__TextureManager__

#include <stdio.h>
#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class TextureManager
{
public:
    
    static TextureManager* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void drawRotatingFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void clearFromTextureMap(std::string id);
    
    std::map<std::string, SDL_Texture*> m_textureMap;
    
private:
    
    TextureManager() {}
    
    static TextureManager* s_pInstance;
    
};

typedef TextureManager TheTextureManager;
#endif /* defined(__Game__TextureManager__) */
