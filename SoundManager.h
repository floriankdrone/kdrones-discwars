//
//  SoundManager.h
//  Game
//
//  Created by Florian D Dutronc on 4/25/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#ifndef __Game__SoundManager__
#define __Game__SoundManager__

#include <stdio.h>
#include <string>
#include <map>

#include <SDL2_mixer/SDL_mixer.h>

enum sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:
    static SoundManager* Instance()
    {
        if (s_pInstance == 0) {
            s_pInstance = new SoundManager();
            return s_pInstance;
        }
        return s_pInstance;
    }
    
    bool load(std::string fileName, std::string id, sound_type type);
    
    void playSound(std::string id, int loop);
    void playMusic(std::string id, int loop);
    
    void stopMusic();

private:
    
    static SoundManager* s_pInstance;
    
    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;
    
    SoundManager();
    ~SoundManager();
    
    SoundManager(const SoundManager&);
    SoundManager &operator=(const SoundManager&);
};

typedef SoundManager TheSoundManager;

#endif /* defined(__Game__SoundManager__) */
