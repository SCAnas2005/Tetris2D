
#include "util.hpp"

void fatal(char *message)
{
    fprintf(stderr, "[-] Error: %s\n", message);
    exit(EXIT_FAILURE);
}

void DestroyAll(SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture)
{
    if (window != NULL) SDL_DestroyWindow(window);
    if (render != NULL) SDL_DestroyRenderer(render);
    if (texture != NULL) SDL_DestroyTexture(texture);

    SDL_Quit();
    return;
}

void fps(Uint64 time)
{   
    if (SDL_GetTicks64() - time < 60)
    {
        SDL_Delay(60 - (SDL_GetTicks() - time));
    }
}

void UpdateGameTime(Uint64 *time, int loop_time)
{
    *time += (SDL_GetTicks64() - loop_time);
}

SDL_Texture *CreateImage(const char *FILENAME, SDL_Renderer *render)
{
    SDL_Surface *surface = IMG_Load(FILENAME);
    SDL_Texture *texture;
    if (surface == NULL)
        return NULL;
    texture = SDL_CreateTextureFromSurface(render, surface);
    if (texture == NULL)
        return NULL;
    SDL_FreeSurface(surface);
    return texture;
}

void SetRect(SDL_Rect *rect, int x, int y, int w, int h)
{
    rect->x = x; rect->y = y; rect->w = w;  rect->h = h;
}

void SetColor(SDL_Color *color, int r, int g, int b, int a)
{
    color->r = r; color->g = g; color->b = b; color->a = a;
}

int DrawImage(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect *rect)
{
    return (SDL_RenderCopy(render, texture, NULL, rect) == 0);
}
void DrawRectangle(SDL_Renderer *render, SDL_Rect rect)
{
    SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
    SDL_RenderDrawRect(render, &rect);
}

char *alloc_memory(int len)
{
    char *ptr = (char *)malloc(len);
    if (ptr == NULL)
        fatal("alloc_memory() failed");
    return ptr;
}


int WriteOnScreen(SDL_Renderer *render, char *text, int x, int y, char *fontname, int size, int r, int g, int b)
{
    SDL_Color color = {r, g, b};
    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface *surface;
    SDL_Texture *texture;

    
    TTF_Font *font = TTF_OpenFont(fontname, size);
    TTF_SizeText(font, text, &rect.w, &rect.h);

    surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
        return 0;

    
    texture = SDL_CreateTextureFromSurface(render, surface);
    if (texture == NULL)    
        return 0;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
        
    SDL_RenderCopy(render, texture, NULL, &rect);

    return 1;
}

void GetFontSize(char *text, char *fontname, int sizefont, int *w, int *h)
{
    TTF_Font *font = TTF_OpenFont(fontname, sizefont);
    if (font == NULL)
        fatal("GetFontSize() failed");

    TTF_SizeText(font, text, w, h);
    TTF_CloseFont(font);
}

void SetIcon(SDL_Window *window, char *filename)
{
    SDL_Surface *icon = IMG_Load(filename);
    if (icon == NULL)
        return;
    
    SDL_SetWindowIcon(window, icon);
}

void PrintConsoleRect(SDL_Rect rect)
{
    printf("Rect:\n");
    printf("X: %d | Y: %d | W: %d | H: %d\n", rect.x, rect.y, rect.w, rect.h);
    return;
}

void SetMusic(int *music, int value)
{
    if( value == 1 || value == 0 )
    {
        *music = value;
    }
}

void SetSound(int *sound, int value)
{
    if ( value == 1 || value == 0 )
    {
        *sound = value;
    }
}