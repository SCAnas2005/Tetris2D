
#ifndef __IMAGE__CPP__
#define __IMAGE__CPP__

    #include "../src/util.hpp"

    class Image
    {
        private:
            char *_filename;
            SDL_Texture *texture;
            SDL_Rect rect;
        public:
            Image();
            Image(char *filename, int x, int y, int w, int h) 
            {
                if (filename != NULL)
                {
                    _filename = alloc_memory(strlen(filename));
                    strcpy(_filename, filename);
                    SetRect(&rect, x, y, w, h);
                }
            }

            int Init(SDL_Renderer *render)
            {
                texture = CreateImage(_filename, render);
                if (texture == NULL)
                    fatal("(Image) Init() : CreateImage() failed");
                return 1;
            }

            int Draw(SDL_Renderer *render)
            {
                return DrawImage(render, texture, &rect);
            }

            ~Image()
            {
                if (_filename != NULL)
                    free(_filename);
                if (texture != NULL)
                    SDL_DestroyTexture(texture);
            }
    };

#endif