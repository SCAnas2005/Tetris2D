
#ifndef __GAMEOVER__CPP__
#define __GAMEOVER__CPP__

    #include <SDL.h>
    #include "util.hpp"
    #include "../Components/button.hpp"
    #include "../Components/image.hpp"

    #define GAMEOVER_SCREEN_IMAGE IMAGEFOLDER"gameover_image.png" 
    #define TRYAGAIN_BUTTON_IMAGE IMAGEFOLDER"tryagain_button.png"

    class GameOver
    {
        public:
            static Image *background;

            static Button *TryagainButton;


            static int InitScreen(SDL_Renderer *render);
            static int InitButton(SDL_Renderer *render);
            static int InitGameOverScreen(SDL_Renderer *render);

            static int IsButtonClicked(int x, int y);

            static int DrawScreen(SDL_Renderer *render);
            static int DrawButton(SDL_Renderer *render);
            static int DrawGameOverScreen(SDL_Renderer *render);

            static void DestroyGameOverScreen();
    };
    

#endif