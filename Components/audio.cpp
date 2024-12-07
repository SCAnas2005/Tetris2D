
#include "audio.hpp"

AudioManager::AudioManager()
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        fatal("AudioManager Constructor: Mix_OpenAudio() failed");
    }
    Music = NULL;
}


int AudioManager::InitMusic(char *filename)
{
    Music = Mix_LoadMUS(filename);
    if (Music == NULL)
        return 0;
    return 1;
}

int AudioManager::PlayMusic()
{
    if (Mix_PlayMusic(Music, -1) == -1)
        return 0;
    return 1;
}



int AudioManager::StopMusic()
{
    if (Mix_HaltMusic() == 0)
        return 1;
    return 0;
}

int AudioManager::PlaySound(Mix_Chunk *sound)
{
    if (sound == NULL)
        return 0;
    Mix_PlayChannel(-1, sound, 0);
    return 1;
}

int AudioManager::StopSound()
{
    Mix_HaltChannel(-1);
    return 1;
}

AudioManager::~AudioManager()
{
    if (Music != NULL)
        Mix_FreeMusic(Music);
    Mix_CloseAudio();
}

Mix_Chunk *AudioManager::CreateSound(char *filename)
{
    return Mix_LoadWAV(filename);
}