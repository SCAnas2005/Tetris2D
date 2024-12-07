
#include <stdio.h>
#include <stdlib.h>

#include "grid.hpp"

void ClearBackground(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, 255,255,255,255);
    SDL_RenderClear(render);
}

void DrawGridSpace(SDL_Renderer *render)
{
    SDL_Rect rect = {PADX-1, PADY-1, COLS*CASE_SIZE, LINES*CASE_SIZE};
    SDL_SetRenderDrawColor(render, 70,26,172,255);
    SDL_RenderFillRect(render, &rect);
}

void DrawBackground(SDL_Renderer *render, SDL_Texture *BackgroundTexture)
{
    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGTH};
    SDL_RenderCopy(render, BackgroundTexture, NULL, &rect);
}

void FillEmptyGrid(char grid[LINES][COLS], char v)
{
    for (int l = 0; l < LINES; l++) {
        for (int c = 0; c < COLS; c++) {
            grid[l][c] = v;
        }
    }
}

void PrintConsoleGrid(char grid[LINES][COLS])
{
    for (int l = 0; l < LINES; l++) {
        for (int c = 0; c < COLS; c++)
        {
            if (c == 0)
                printf("\t");
            printf("%c ", grid[l][c]);
        }
        printf("\n");
    }
}

void FillRectGrid(SDL_Rect RectGrid[LINES][COLS])
{
    SDL_Rect rect = {0,0,0,0};
    for (int l = 0; l < LINES; l++) {
        for (int c = 0; c < COLS; c++) {
            rect.x = c * CASE_SIZE + PADX; rect.y = l * CASE_SIZE+PADY; rect.w = CASE_SIZE; rect.h = CASE_SIZE;
            RectGrid[l][c] = rect;
        }
    }
}   

void DrawRectGrid(SDL_Renderer *render, SDL_Rect RectGrid[LINES][COLS])
{
    SDL_SetRenderDrawColor(render, 255,255,255,255);
    SDL_Rect rect = {RectGrid[0][0].x, RectGrid[0][0].y, COLS*CASE_SIZE, LINES*CASE_SIZE};
    SDL_RenderDrawRect(render, &rect);

    for (int l = 0; l < LINES; l++) {
        for (int c = 0; c < COLS; c++) {
            SDL_RenderDrawRect(render, &RectGrid[l][c]);
        }
    }
}

int IsGamerOver(char grid[LINES][COLS])
{
    for (int i = 0; i < COLS; i++)
    {
        if (grid[0][i] == 'b')
            return 1;
    }
    return 0;
}

int IsFullLine(char grid[LINES][COLS])
{
    int cols_number = 0; 
    for (int l = 0; l < LINES; l++)
    {
        cols_number = 0;
        for (int c = 0; grid[l][c] == 'b' && c < COLS; c++)
        {
            cols_number++;
        }
        if (cols_number == COLS)
            return l;
    }
    return -1;
}

int SetLineEmpty(char grid[LINES][COLS], int &line_number)
{
    line_number = IsFullLine(grid);
    if (line_number == -1)
        return 0;

    for (int i = 0; i < COLS; i++)
    {
        grid[line_number][i] = 'v';
    }
    SetGridLineDown(grid, line_number);
    return 1;
}


void SetGridLineDown(char grid[LINES][COLS], int line_number)
{
    for (int l = line_number; l >= 0; l--)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (l > 0)
                grid[l][c] = grid[l-1][c];
            else    
                grid[l][c] = 'v';
        }
    }
}

int IsEmptyGridPlace(int l, int c, char name, char grid[LINES][COLS])
{
    return (grid[l][c] == 'v' || grid[l][c] == name);
}

void SetGridName(int l, int c, char name, char grid[LINES][COLS])
{
    grid[l][c] = name;
}