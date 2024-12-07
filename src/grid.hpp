
#ifndef __GRID__CPP__
#define __GRID__CPP__

    #include <SDL.h>
    #include <SDL_image.h>
    #include "util.hpp"

    #define BACKGROUND_FILENAME IMAGEFOLDER"game_background_image.png"

    #define WINDOW_WIDTH 1080
    #define WINDOW_HEIGTH 720

    #define LINES 23
    #define COLS 12

    #define CASE_SIZE 30
    #define PADX (WINDOW_WIDTH - (COLS*CASE_SIZE)) / 2 + 150
    #define PADY 10


    void ClearBackground(SDL_Renderer *render);
    void DrawGridSpace(SDL_Renderer *render);
    void FillEmptyGrid(char grid[LINES][COLS], char v);
    void PrintConsoleGrid(char grid[LINES][COLS]); 
    void FillRectGrid(SDL_Rect RectGrid[LINES][COLS]);
    void DrawRectGrid(SDL_Renderer *render, SDL_Rect RectGrid[LINES][COLS]);
    int IsGamerOver(char grid[LINES][COLS]);
    void SetGridLineDown(char grid[LINES][COLS], int line_number);

    int IsFullLine(char grid[LINES][COLS]);
    int SetLineEmpty(char grid[LINES][COLS], int &line_number);

    SDL_Texture *InitBackgroundImage(SDL_Renderer *render);
    void DrawBackground(SDL_Renderer *render, SDL_Texture *BackgroundTexture);
    int IsEmptyGridPlace(int l, int c, char name, char grid[LINES][COLS]);
    void SetGridName(int l, int c, char name, char grid[LINES][COLS]);
    

#endif