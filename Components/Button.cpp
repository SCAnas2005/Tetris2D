
#include "button.hpp"
#include <string.h>

Button::Button(char *FilenameImage, char *textParam, int x, int y, int w, int h)
{
    if (FilenameImage == NULL)
        filename = NULL;
    else {filename = alloc_memory(strlen(FilenameImage)); strcpy(filename, FilenameImage);}
    if (textParam == NULL)
        text = NULL;
    else {text = alloc_memory(strlen(textParam)); strcpy(text, textParam);}

    SetRect(&rect, x, y, w, h);
    ImageSelected = 0;
    active = 0;
    ImagesNumber = 0;
}

int Button::Init(SDL_Renderer *render)
{
    return AddImage(render, filename);
}   

int Button::Draw(SDL_Renderer *render)
{
    if (ImagesTextures[ImageSelected] != NULL)
    {
        if (DrawImage(render, ImagesTextures[ImageSelected], &rect) == 0)
            return 0;
    }
    return 1;
}

int Button::IsClicked(int x, int y)
{
    if ((x >= rect.x && x <= rect.x+rect.w) && (y >= rect.y && y <= rect.y+rect.h))
    {
        return 1;
    }
    return 0;
}

void Button::DrawRect(SDL_Renderer *render)
{
    DrawRectangle(render, rect);
}

void Button::animate()
{
    if (active)
    {
        rect.x += 10; rect.y += 5;
        rect.w -= 20; rect.h -= 10;
    }
    else 
    {
        rect.x -= 10; rect.y -= 5;
        rect.w += 20; rect.h += 10;
    } 
}

int Button::AddImage(SDL_Renderer *render, char *filename)
{
    SDL_Texture *NewTexture = CreateImage(filename, render);
    if (NewTexture == NULL)
        fatal("(Button) AddImage() failed");
    ImagesTextures[ImagesNumber] = NewTexture;
    ImagesNumber++;
    return 1;
}

int Button::ChangeImage(int index)
{
    if (index >= 0 && index < ImagesNumber)
    {
        ImageSelected = index;
        return 1;
    }
    return 0;
}   

Button::~Button()
{
    if (filename != NULL)
        free(filename);
    if (text != NULL)
        free(text);
    for (int i = 0; i < ImagesNumber; i++)
    {
        if (ImagesTextures[i] != NULL)
            SDL_DestroyTexture(ImagesTextures[i]);
    }
}