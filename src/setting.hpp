
#ifndef __SETTING__CPP__
#define __SETTING__CPP__

    #include "../Components/button.hpp"
    #include "../Components/image.hpp"
    #include "../Components/text.hpp"

    #define MUSIC_SETTING_IMAGE IMAGEFOLDER"music_button.png"
    #define SOUND_SETTING_IMAGE IMAGEFOLDER"sound_button.png"
    #define SETTINGELEMENTNUMBER 2

    #define MUSIC 0
    #define SOUND 1

    typedef int (*CALLBACK)();  // type function for Command method

    class SettingObject
    {
        private: 
            SDL_Rect storage;
            
            Text *name;
            Button *button;
        public:
            SettingObject() {}
            SettingObject(char *text, char *filename, int x, int y, int w, int h);

            int Init(SDL_Renderer *render);
            int Draw(SDL_Renderer *render);

            int SetNewImage(SDL_Renderer *render, char *filename);
            Button *GetButton() { return button; }

            int IsClicked(int x, int y);
            
            ~SettingObject();
    };

    class Setting
    {
        public:
            static int x;
            static int y;

            static int ElementNumber;
            static SettingObject *Objects[SETTINGELEMENTNUMBER];

            static int Init(SDL_Renderer *render);
            static int Draw(SDL_Renderer *render);

            static int IsMusicClicked(int x, int y);
            static int IsSoundClicked(int x, int y);

            static Button *GetMusicButton() { return Objects[MUSIC]->GetButton(); }
            static Button *GetSoundButton() { return Objects[SOUND]->GetButton(); }

            static void Destroy();
    };  



#endif