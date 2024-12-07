
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util.hpp"
#include "grid.hpp"
#include "bloc.hpp"
#include "homescreen.hpp"
#include "timer.hpp"
#include "stream.hpp"
#include "gameover.hpp"
#include "setting.hpp"

#include "../Components/audio.hpp"
#include "globals.hpp"

void DrawDisabledShapes(SDL_Renderer *render, SDL_Rect GridRect[LINES][COLS], 
char grid[LINES][COLS], Shape DisabledShapes[], int num);
void NewDisabledShapes(Shape DisabledShapes[], int &DisabledShapesNumber, Shape *SelectedShape);
void NewSelectedShape(Shape *SelectedShape, Shape *ListShapes[], char grid[LINES][COLS]);
void RemoveShapeLine(Shape DisabledShapes[], int num, int line_number, char grid[LINES][COLS]);

void DrawNextShapeSpace(SDL_Renderer *render);
int WriteNextShape(SDL_Renderer *render, char *text);
int WriteVersion(SDL_Renderer *render, char *version_buffer);
int WriteScore(SDL_Renderer *render, int score);
int WriteBestScore(SDL_Renderer *render, int BestScore);
int WriteTimer(SDL_Renderer *render, Timer *timer);
int WriteBestTime(SDL_Renderer *render, int BestTime);
int WriteLevel(SDL_Renderer *render);

void SetBestScore(int &BestScore, int score);
void SetBestTime(int &BestTime, Timer &timer);

int main(int argc, char *argv[])
{
    int SCREEN_STATE = SCREEN_HOMESCREEN;
    char grid[LINES][COLS];
    SDL_Rect RectGrid[LINES][COLS]; 

    // shape created here 
    Shape *SelectedShape;
    Shape *NextShape;
    Shape *ShapeList[] = {new Square(), new Line(), new Stair(), new Foot(), new Pyramid()};
    Shape DisabledShapes[1000] = {};
    int DisabledShapesNumber = 0;

    Uint64 loop_time = 0;                   // One loop milliseconds time
    Uint64 game_time = 0;                   // all game milliseconds time
    int Score = 0;
    int BestScore = 0;
    int BestTime = 0;
    char version[10];
    

    int NewShapeAllowed = 0;                // Create new shape state
    int FullLine = -1;
    int ShapeSpeedTime = DEFAULT_SHAPE_SPEED_TIME;  // 300 ms to move
    int rotate_pressed = 0;                 // Rotate button pressed
    int random_index;                       // random index to choose


    int MusicSet = 1;
    int SoundSet = 1;
    AudioManager Audio{};                  // Init the audio manager
    Mix_Chunk *BlocSound = AudioManager::CreateSound(BLOC_SOUND_FILENAME);
    Mix_Chunk *GameOverSound = AudioManager::CreateSound(GAMEOVER_SOUND_FILENAME);

    Timer game_timer;

    // Windows and renderer 
    SDL_Window *window;
    SDL_Renderer *render;
    Image *GameBackground;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fatal("SDL_Init() failed");

    if (!IMG_Init(IMG_INIT_PNG))
        fatal("IMG_Init() failed");
    if (TTF_Init() == -1)
        fatal("TTF_Init() failed");
    if (!Mix_Init(MIX_INIT_OGG))
        fatal("Mix_Init() failed");

    srand(time(NULL));

    window = SDL_CreateWindow("TETRIS", 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGTH, 0);
    if (window == NULL)
    {
        fatal("SDL_CreateWindow() failed");
    }
    SetIcon(window, IMAGEFOLDER"icon.png");
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (render == NULL)
    {
        DestroyAll(window, NULL, NULL);
        fatal("SDL_CreateRenderer() failed");
    }

    GameBackground = new Image(BACKGROUND_FILENAME, 0,0, WINDOW_WIDTH,WINDOW_HEIGTH);
    GameBackground->Init(render);

    FillRectGrid(RectGrid);
    if (Home::InitHomeScreen(render) == 0)
        fatal("(Home) InitHomeScreen() failed");
    if (Home::InitHomeButton(render) == 0)
        fatal("(Home) InitHomeButton() failed");
    
    GetUserStats(&BestScore, &BestTime);

    if (!Audio.InitMusic(MUSIC_FILENAME))
    {
        fatal("(Audio) InitMusic() failed");
    }

    if (!GetVersion(version))
        fatal("GetVersion() failed");

    SDL_bool started = SDL_TRUE;
    while (started)
    {
        loop_time = SDL_GetTicks64();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    started = SDL_FALSE;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (SCREEN_STATE == SCREEN_HOMESCREEN)
                    {
                        if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            if (SCREEN_STATE == SCREEN_HOMESCREEN)
                            {
                                if (Home::PlayButton->IsClicked(event.motion.x, event.motion.y)) 
                                {
                                    Home::PlayButton->SetActive(1);
                                }
                                else if (Home::SettingButton->IsClicked(event.motion.x, event.motion.y)) 
                                {    
                                    Home::SettingButton->SetActive(1);
                                }
                            }

                        }
                    }
                    if (SCREEN_STATE == SCREEN_GAMEOVER)
                    {
                        if (GameOver::IsButtonClicked(event.motion.x, event.motion.y))
                        {
                            if (SoundSet)
                                Audio.StopSound();
                            SCREEN_STATE = SCREEN_INITGAMESCREEN;
                        }
                    }
                    if (SCREEN_STATE == SCREEN_GAMESCREEN || SCREEN_STATE == SCREEN_SETTINGSCREEN 
                    || SCREEN_STATE == SCREEN_GAMEOVER)
                    {
                        if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            if (Home::HomeButton->IsClicked(event.motion.x, event.motion.y))
                            {
                                Home::HomeButton->SetActive(1);
                            }
                        }
                    }

                    if (SCREEN_STATE == SCREEN_SETTINGSCREEN)
                    {
                        if (Setting::IsMusicClicked(event.motion.x, event.motion.y))
                        {
                            if (!MusicSet)
                                SetMusic(&MusicSet, 1);
                            else 
                                SetMusic(&MusicSet, 0);
                        }
                        else if (Setting::IsSoundClicked(event.motion.x, event.motion.y))
                        {
                            if(!SoundSet)
                                SetSound(&SoundSet, 1);
                            else 
                                SetSound(&SoundSet, 0);
                        }
                    }
                    
                break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SCREEN_STATE == SCREEN_HOMESCREEN)
                        {
                            if (Home::PlayButton->IsActive())
                            {
                                Home::PlayButton->SetActive(0);
                                SCREEN_STATE = SCREEN_INITGAMESCREEN;
                            }
                            else if (Home::SettingButton->IsActive())
                            {
                                Home::SettingButton->SetActive(0);
                                SCREEN_STATE = SCREEN_INITSETTINGSCREEN;
                            }
                        }
                        if (SCREEN_STATE == SCREEN_GAMESCREEN || SCREEN_STATE == SCREEN_SETTINGSCREEN 
                        || SCREEN_STATE == SCREEN_GAMEOVER)
                        {
                            if (Home::HomeButton->IsActive())
                            {
                                Home::HomeButton->SetActive(0);
                                if (SCREEN_STATE == SCREEN_GAMESCREEN)
                                {
                                    DisabledShapesNumber = 0;
                                    game_timer.ResetTimer();
                                    Score = 0;
                                    ShapeSpeedTime = DEFAULT_SHAPE_SPEED_TIME;

                                    Audio.StopMusic();
                                }
                                else if (SCREEN_STATE == SCREEN_GAMEOVER)
                                {
                                    GameOver::DestroyGameOverScreen();
                                    if (SoundSet)
                                        Audio.StopSound();
                                }
                                else if (SCREEN_STATE == SCREEN_SETTINGSCREEN);
                                {
                                    Setting::Destroy();
                                }

                                SCREEN_STATE = SCREEN_HOMESCREEN;
                            }
                        }
                    }
                break;  

                case SDL_KEYDOWN:
                    if (SCREEN_STATE == SCREEN_GAMESCREEN)
                    {
                        if (event.key.keysym.sym == SDLK_RIGHT)
                        {
                            SelectedShape->MoveRight(grid);
                        }
                        else if (event.key.keysym.sym == SDLK_LEFT)
                        {
                            SelectedShape->MoveLeft(grid);
                        }
                        else if (event.key.keysym.sym == SDLK_DOWN)
                        {
                            ShapeSpeedTime = 50;
                        }
                        else if (event.key.keysym.sym == SDLK_UP)
                        {
                            if (!rotate_pressed)
                            {
                                SelectedShape->Rotate(grid);
                                rotate_pressed = 1;
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_SPACE)
                        {
                            game_timer.PrintConsoleTime();
                        }
                    }
                    
                break;

                case SDL_KEYUP:
                    if (SCREEN_STATE == SCREEN_GAMESCREEN)
                    {
                        if (event.key.keysym.sym == SDLK_DOWN)
                        {
                            ShapeSpeedTime = DEFAULT_SHAPE_SPEED_TIME;
                        }
                        else if (event.key.keysym.sym == SDLK_UP)
                        {
                            if (rotate_pressed)
                                rotate_pressed = 0;
                        }
                    }
                break;
                
                default:
                break;
            }
        }
        ClearBackground(render);
        if (SCREEN_STATE == SCREEN_HOMESCREEN)
        {
            Home::DrawHomeScreen(render);
        }
        else if (SCREEN_STATE == SCREEN_INITGAMESCREEN)
        {
            FillEmptyGrid(grid, 'v');
            random_index = rand()%5;
            SelectedShape = ShapeList[random_index];
            SelectedShape->Init(0, COLS/2, grid);

            NextShape = ShapeList[rand()%5];
            NewShapeAllowed = 0;

            game_timer.InitTimer();
            SCREEN_STATE = SCREEN_GAMESCREEN;

            if (MusicSet == 1)
            {
                Audio.PlayMusic();
            }
        }
        else if (SCREEN_STATE == SCREEN_GAMESCREEN)
        {
            // AFFICHAGE
            GameBackground->Draw(render);
            DrawGridSpace(render);
            DrawNextShapeSpace(render);
            NextShape->DrawNextShape(render);
            Home::DrawHomeButton(render);

            if (!WriteNextShape(render, "NEXT SHAPE"))
                fatal("WriteNextShape() failed");
            if (!WriteVersion(render, version))
                fatal("WriteVersion() failed");
            if (!WriteScore(render, Score))
                fatal("WriteScore() failed");
            if (!WriteBestScore(render, BestScore))
                fatal("WriteBestScore() failed");
            if (!WriteTimer(render, &game_timer))
                fatal("WriteTimer() failed");
            if (!WriteBestTime(render, BestTime))
                fatal("WriteBestTime() failed\n");
            if (!WriteLevel(render))
                fatal("WriteLevel() failed");
            
            DrawRectGrid(render, RectGrid);
            SelectedShape->Draw(render, RectGrid, grid);

            // ACTION
            SelectedShape->MoveDown(game_time, grid, &NewShapeAllowed, ShapeSpeedTime);
            DrawDisabledShapes(render, RectGrid, grid, DisabledShapes, DisabledShapesNumber);
            if (IsGamerOver(grid))
            {
                SetBestTime(BestTime, game_timer);
                SetBestScore(BestScore, Score);
                SelectedShape = NULL;
                NextShape = NULL;
                DisabledShapesNumber = 0;
                game_timer.ResetTimer();
                Score = 0;
                ShapeSpeedTime = DEFAULT_SHAPE_SPEED_TIME;

                if (!GameOver::InitGameOverScreen(render)) 
                    fatal("(GameOver) InitScreen() failed");

                Audio.StopMusic();
                if (SoundSet == 1)
                {
                    if (!Audio.PlaySound(GameOverSound))
                        fatal("(AudioManager) PlaySound() failed");
                }
                SCREEN_STATE = SCREEN_GAMEOVER;
                continue;
            }

            if (NewShapeAllowed)
            {
                if (SoundSet == 1)
                    Audio.PlaySound(BlocSound);

                NewDisabledShapes(DisabledShapes, DisabledShapesNumber, SelectedShape); 
                random_index = rand()%5;
                SelectedShape = NextShape;
                SelectedShape->Init(0, COLS/2, grid);
                NextShape = ShapeList[random_index];

                NewShapeAllowed = 0;
            }
            while (SetLineEmpty(grid, FullLine))
            {
                RemoveShapeLine(DisabledShapes, DisabledShapesNumber, FullLine, grid);
                Score += (COLS*10);
                SetBestScore(BestScore, Score);
            }
            game_timer.UpdateTimer(SDL_GetTicks64() - loop_time);
            SetBestTime(BestTime, game_timer);
        }
        else if (SCREEN_STATE == SCREEN_INITSETTINGSCREEN)
        {
            if (!Setting::Init(render))
                fatal("(Setting) Init() failed");
            Setting::GetMusicButton()->ChangeImage(MusicSet);
            Setting::GetSoundButton()->ChangeImage(SoundSet);
            SCREEN_STATE = SCREEN_SETTINGSCREEN;
        }
        else if (SCREEN_STATE == SCREEN_SETTINGSCREEN)
        {
            Home::DrawBackground(render);
            Home::DrawHomeButton(render);
            if (!Setting::Draw(render))
                fatal("Error: (Setting) Draw() failed");
        }
        else if (SCREEN_STATE == SCREEN_GAMEOVER)
        {
            GameOver::DrawGameOverScreen(render);
            Home::DrawHomeButton(render);
        }

        SDL_RenderPresent(render);
        fps(loop_time);
        UpdateGameTime(&game_time, loop_time);
    }

    SaveUserStats(BestScore, BestTime);

    Home::DestroyHomeScreenObjects();
    DestroyAll(window, render, NULL);
    delete GameBackground;


    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void NewDisabledShapes(Shape DisabledShapes[], int &DisabledShapesNumber, Shape *SelectedShape)
{
    DisabledShapes[DisabledShapesNumber] = *SelectedShape;
    DisabledShapesNumber++;
}

void NewSelectedShape(Shape *SelectedShape, Shape *ListShapes[], char grid[LINES][COLS])
{
    int random_index = rand()%5;
    SelectedShape = ListShapes[random_index];
    SelectedShape->Init(0,5,grid);
}

void DrawDisabledShapes(SDL_Renderer *render, SDL_Rect GridRect[LINES][COLS], 
char grid[LINES][COLS], Shape DisabledShapes[], int num)
{
    for (int i = 0; i < num; i++)
    {
        DisabledShapes[i].Draw(render, GridRect, grid);
    }
}

void RemoveShapeLine(Shape DisabledShapes[], int num, int line_number, char grid[LINES][COLS])
{
    Pos pos;
    for (int i = 0; i < num; i++)
    {
        DisabledShapes[i].DelSubShapes(line_number, grid);
    }
}

void DrawNextShapeSpace(SDL_Renderer *render)
{
    SDL_Rect rect = {NEXTSHAPE_SPACE_X, NEXTSHAPE_SPACE_Y, NEXTSHAPE_SPACE_SIZE, NEXTSHAPE_SPACE_SIZE};
    SDL_RenderFillRect(render, &rect);
}

int WriteNextShape(SDL_Renderer *render, char *text)
{
    SDL_Color color = {255,255,255,255};
    if(WriteOnScreen(render, text, 
    NEXTSHAPE_SPACE_X, NEXTSHAPE_SPACE_Y-50, DEFAULT_FONT, 30, color.r, color.g, color.b))
        return 1;
    return 0;
}


int WriteVersion(SDL_Renderer *render, char *version_buffer)
{
    char VersionText[20] = "TETRIS ";
    strcat(VersionText, version_buffer);
    SDL_Color color = {255,255,255,255};
    return WriteOnScreen(render, VersionText, 20, 20, DEFAULT_FONT, 30, color.r, color.g, color.b);
}

int WriteScore(SDL_Renderer *render, int score)
{
    char ScoreText[50];
    sprintf(ScoreText, "Score : %d", score);
    SDL_Color color = {255,255,255,255};

    if (WriteOnScreen(render, ScoreText, 200,WINDOW_HEIGTH - 300, DEFAULT_FONT, 30, color.r, color.g, color.b))
        return 1;
    return 0;
}

int WriteBestScore(SDL_Renderer *render, int BestScore)
{
    char BestScoreText[50];
    sprintf(BestScoreText, "Best Score : %d", BestScore);
    SDL_Color color = {255,255,255,255};
    return (WriteOnScreen(render, BestScoreText, 200,WINDOW_HEIGTH-250, DEFAULT_FONT, 30, color.r, color.g, color.b));
}

int WriteTimer(SDL_Renderer *render, Timer *timer)
{
    char TimeText[30];
    sprintf(TimeText, "Time : %d", timer->MsToS());
    SDL_Color color = {255,255,255,255};
    return WriteOnScreen(render, TimeText, 200, WINDOW_HEIGTH-200, DEFAULT_FONT, 30, color.r, color.g, color.b);
}   

int WriteBestTime(SDL_Renderer *render, int BestTime)
{
    char BestTimeText[30];
    sprintf(BestTimeText, "Best Time : %d", BestTime);
    SDL_Color color = {255,255,255,255};
    return WriteOnScreen(render, BestTimeText, 200, WINDOW_HEIGTH-150, DEFAULT_FONT, 30, color.r, color.g, color.b); 
}

int WriteLevel(SDL_Renderer *render)
{
    char LevelText[20] = "Level : 1";
    SDL_Color color = {255,255,255,255};
    return WriteOnScreen(render, LevelText, 200, WINDOW_HEIGTH-100, DEFAULT_FONT, 30, color.r, color.g, color.b);
}

void SetBestScore(int &BestScore, int score)
{
    if (score > BestScore)
        BestScore = score;
}

void SetBestTime(int &BestTime, Timer &timer)
{
    if (timer.MsToS() > BestTime)
        BestTime = timer.MsToS();
}