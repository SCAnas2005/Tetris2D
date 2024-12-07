
#ifndef __AUDIO__CPP__
#define __AUDIO__CPP__

    #include "../src/util.hpp"

    #define MUSIC_FILENAME AUDIOFOLDER"main_music.mp3"

    #define GAMEOVER_SOUND_FILENAME AUDIOFOLDER"gameover_sound.wav"
    #define BLOC_SOUND_FILENAME AUDIOFOLDER"bloc_sound.wav"

    class AudioManager
    {
        private:
            Mix_Music *Music;

        public:
            AudioManager();
            int InitMusic(char *filename);
            int PlayMusic();
            int StopMusic();

            int PlaySound(Mix_Chunk *sound);
            int StopSound();

            static Mix_Chunk *CreateSound(char *filename);

            ~AudioManager();
    };


#endif