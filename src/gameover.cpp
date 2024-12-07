
#include "gameover.hpp"
#include <stdio.h>

#include "globals.hpp"

Image *GameOver::background = NULL;
Button *GameOver::TryagainButton = NULL;

int GameOver::InitScreen(SDL_Renderer *render)
{
    GameOver::background = new Image(GAMEOVER_SCREEN_IMAGE, 0,0,WINDOW_WIDTH, WINDOW_HEIGTH);
    return GameOver::background->Init(render);
}

int GameOver::InitButton(SDL_Renderer *render)
{   
    GameOver::TryagainButton = new Button(TRYAGAIN_BUTTON_IMAGE, NULL, 150, WINDOW_HEIGTH-120, 125, 110);
    return GameOver::TryagainButton->Init(render);
}

int GameOver::InitGameOverScreen(SDL_Renderer *render)
{
    if (!GameOver::InitScreen(render))
        return 0;
    if (!GameOver::InitButton(render))
        return 0;
    return 1;
}

int GameOver::DrawScreen(SDL_Renderer *render)
{
    return GameOver::background->Draw(render);
}

int GameOver::DrawButton(SDL_Renderer *render)
{
    return GameOver::TryagainButton->Draw(render);
}

int GameOver::DrawGameOverScreen(SDL_Renderer *render)
{
    if (!GameOver::DrawScreen(render))
        return 0;
    if (!GameOver::DrawButton(render))
        return 0;
    return 1;
}

void GameOver::DestroyGameOverScreen()
{
    delete GameOver::background;
    delete GameOver::TryagainButton;
}


int GameOver::IsButtonClicked(int x, int y)
{
    return GameOver::TryagainButton->IsClicked(x, y);
}