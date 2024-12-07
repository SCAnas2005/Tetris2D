
#ifndef __BUTTON__CPP__
#define __BUTTON__CPP__

    #include "../src/util.hpp"

    class Button
    {
        private:
            char *filename;
            char *text;
            
            SDL_Rect rect;

            SDL_Texture *ImagesTextures[5];
            int ImageSelected;
            int ImagesNumber;

            int active;
        public:
            Button() {}
            Button(char *FilenameImage, char *textParam, int x, int y, int w, int h);
            int Init(SDL_Renderer *render);
            int Draw(SDL_Renderer *render);
            void DrawRect(SDL_Renderer *);
            SDL_Rect GetRect() { return rect; };
            int IsClicked(int x, int y);
            void animate();

            int AddImage(SDL_Renderer *render, char *filename);
            int ChangeImage(int index);
            int GetIndexImage() { return ImageSelected; }

            int IsActive() { return active; }
            void SetActive(int value) { active = value; animate(); }
            ~Button();
    };

#endif