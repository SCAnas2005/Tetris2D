
#ifndef __HOMESCREEN__CPP__
#define __HOMESCREEN__CPP__

    #include <SDL.h>
    #include <SDL_image.h>
    #include "../Components/button.hpp"
    #include "../Components/image.hpp"

    #define BACKGROUND_IMAGE_FILENAME IMAGEFOLDER"background_image.png"
    #define TITLE_IMAGE_FILENAME IMAGEFOLDER"title_image.png"
    #define PLAYBUTTON_FILENAME IMAGEFOLDER"play_button.png"
    #define SETTINGBUTTON_FILENAME IMAGEFOLDER"setting_button.png"
    #define HOMEBUTTON_FILENAME IMAGEFOLDER"home_button.png"

    class Home
    {
        public:
            static Image *background;
            static Image *title;
            
            static Button *PlayButton;
            static Button *SettingButton;
            static Button *HomeButton;

            static int InitBackgroundImage(SDL_Renderer *render);
            static int InitTitleImage(SDL_Renderer *render);
            static int InitButtonImages(SDL_Renderer *render);
            static int InitHomeScreen(SDL_Renderer *render);
            static int InitHomeButton(SDL_Renderer *render);

            static int IsButtonPushed(SDL_Rect &rect, int x, int y);
            static void ButtonPushed(SDL_Rect &rect);
            static void ButtonLoose(SDL_Rect &rect);

            static void DrawBackground(SDL_Renderer *render);
            static void DrawTitle(SDL_Renderer *render);
            static void DrawHomeButton(SDL_Renderer *render);
            static void DrawButtons(SDL_Renderer *render);
            static void DrawHomeScreen(SDL_Renderer *render);


            static void DestroyHomeScreenObjects();
            static void DestroyHomeButton();
    };


#endif