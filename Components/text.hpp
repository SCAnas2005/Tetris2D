
#ifndef __TEXT__CPP__
#define __TEXT__CPP__

    #include "../src/util.hpp"

    class Text
    {
        private:
            char *_content;
            char *_FontName;
            int _FontSize;

            SDL_Color color;

            SDL_Rect rect;
        public:
            Text();
            Text(char *text, char *FontName, int FontSize, int r, int g, int b, int x, int y, int w, int h);
            SDL_Rect GetRect() { return rect; }
            int Write(SDL_Renderer *render);
            ~Text();
    };



#endif