
#ifndef __UTIL__CPP__
#define __UTIL__CPP__

    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>



    typedef struct pos{
        int l;
        int c;
    } Pos;

    char *alloc_memory(int len);
    void fatal(char *message);
    void DestroyAll(SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture);
    void fps(Uint64 time);
    void UpdateGameTime(Uint64 *time, int loop_time);
    SDL_Texture *CreateImage(const char *FILENAME, SDL_Renderer *render);
    void SetRect(SDL_Rect *rect, int x, int y, int w, int h);
    void SetColor(SDL_Color *color, int r, int g, int b, int a);
    int DrawImage(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect *rect);
    void DrawRectangle(SDL_Renderer *render, SDL_Rect rect);
    int WriteOnScreen(SDL_Renderer *render, char *text, int x, int y, char *fontname, int size, int r, int g, int b);

    void SetIcon(SDL_Window *window, char *filename);
    void GetFontSize(char *text, char *fontname, int sizefont, int *w, int *h);

    void PrintConsoleRect(SDL_Rect rect);
    void SetMusic(int *music, int value);
    void SetSound(int *sound, int value);
#endif