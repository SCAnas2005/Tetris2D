
#include <stdio.h>
#include "homescreen.hpp"
#include "util.hpp"
#include "globals.hpp"

Image *Home::background = new Image(BACKGROUND_IMAGE_FILENAME, 0,0,WINDOW_WIDTH,WINDOW_HEIGTH);  

Image *Home::title = new Image(TITLE_IMAGE_FILENAME, 300,20,500,300);

Button *Home::PlayButton = new Button(PLAYBUTTON_FILENAME, NULL, 150, 520, 200, 70);
Button *Home::SettingButton = new Button(SETTINGBUTTON_FILENAME, NULL, 500, 470, 75, 75);
Button *Home::HomeButton = new Button(HOMEBUTTON_FILENAME, NULL, 20, WINDOW_HEIGTH-120, 100,100);

int Home::InitBackgroundImage(SDL_Renderer *render)
{
    return Home::background->Init(render);
}

int Home::InitTitleImage(SDL_Renderer *render)
{
    return Home::title->Init(render);
}

int Home::InitButtonImages(SDL_Renderer *render)
{
    if (Home::PlayButton->Init(render) == 0)
        return 0;
    if (Home::SettingButton->Init(render) == 0)
        return 0;
    return 1;
}

int Home::InitHomeButton(SDL_Renderer *render)
{
    return Home::HomeButton->Init(render);
}

int Home::InitHomeScreen(SDL_Renderer *render)
{   
    if (!InitBackgroundImage(render))
        return 0;
    if (!InitTitleImage(render))
        return 0;
    if (!InitButtonImages(render))
        return 0;
    return 1;
}

void Home::DrawBackground(SDL_Renderer *render)
{
    Home::background->Draw(render);
}

void Home::DrawTitle(SDL_Renderer *render)
{
    Home::title->Draw(render);
}
void Home::DrawHomeButton(SDL_Renderer *render)
{
    Home::HomeButton->Draw(render);
}

void Home::DrawButtons(SDL_Renderer *render)
{
    Home::PlayButton->Draw(render);
    Home::SettingButton->Draw(render);
}


void Home::DrawHomeScreen(SDL_Renderer *render)
{
    Home::DrawBackground(render);
    Home::DrawTitle(render);
    Home::DrawButtons(render);
}

int Home::IsButtonPushed(SDL_Rect &rect, int x, int y)
{
    if ((x >= rect.x && x <= rect.x+rect.w) && (y >= rect.y && x <= rect.y+rect.h))
        return 1;
    return 0;
}

void Home::ButtonPushed(SDL_Rect &rect)
{
    rect.w -= (rect.w / 4);
    rect.h -= (rect.h / 4);
    rect.x += (rect.w / 2);
    rect.y += (rect.w / 2);
}

void Home::ButtonLoose(SDL_Rect &rect)
{
    rect.w += (rect.w / 4);
    rect.h += (rect.h / 4);
    rect.x -= (rect.w / 2);
    rect.y -= (rect.w / 2);
}

void Home::DestroyHomeScreenObjects()
{
    delete Home::background;
    delete Home::title;
    delete Home::PlayButton;
    delete Home::SettingButton;
    delete Home::HomeButton;
}