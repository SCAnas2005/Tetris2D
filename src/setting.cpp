
#include "setting.hpp"
#include "globals.hpp"

SettingObject::SettingObject(char *text, char *filename, int x, int y, int w, int h)
{
    SetRect(&storage, x, y, w, h);
    name = new Text(text, FONTFOLDER"Arial.ttf", 50, 255,255,255, storage.x+15, storage.y+20, 0,0);
    button = new Button(filename, NULL, storage.x+storage.w-130, storage.y, 100, 100);
}

int SettingObject::SetNewImage(SDL_Renderer *render, char *filename)
{
    button->AddImage(render, filename);
    return 1;
}

int SettingObject::Init(SDL_Renderer *render)
{
    return button->Init(render);
}

int SettingObject::Draw(SDL_Renderer *render)
{
    DrawRectangle(render, storage);
    DrawRectangle(render, name->GetRect());
    //printf("Name?\n");
    if (!name->Write(render))
        return 0;
    DrawRectangle(render, button->GetRect());
    //printf("button ?\n");
    if (!button->Draw(render))
        return 0;
    //printf("all works fine\n");
    return 1;
}


int SettingObject::IsClicked(int x, int y)
{
    if (button->IsClicked(x, y))
    {
        if (button->GetIndexImage() == 0)
            button->ChangeImage(1);
        else if (button->GetIndexImage() == 1)
            button->ChangeImage(0);
        return 1;
    }
    return 0;
}   

SettingObject::~SettingObject()
{
    if (name)
        delete name;
    if (button)
        delete button;
}







int Setting::ElementNumber = SETTINGELEMENTNUMBER;
SettingObject *Setting::Objects[SETTINGELEMENTNUMBER] = {NULL};
int Setting::x = (WINDOW_WIDTH-400)/2;
int Setting::y = (WINDOW_HEIGTH-200)/2;

int Setting::Init(SDL_Renderer *render)
{
    Setting::Objects[MUSIC] = new SettingObject("MUSIC : ", MUSIC_SETTING_IMAGE, x, y, 400, 100);   
    Setting::Objects[MUSIC]->SetNewImage(render, IMAGEFOLDER"music_button2.png");
    Setting::Objects[SOUND] = new SettingObject("SOUND : ", SOUND_SETTING_IMAGE, x, y+100, 400, 100);
    Setting::Objects[SOUND]->SetNewImage(render, IMAGEFOLDER"sound_button2.png");

    for (int i = 0; i < Setting::ElementNumber; i++)
    {
        if (!Setting::Objects[i]->Init(render))
            return 0;
    }
    return 1;
}

int Setting::Draw(SDL_Renderer *render)
{
    for (int i = 0; i < Setting::ElementNumber; i++)
    {
        if (!Setting::Objects[i]->Draw(render))
            return 0;
    }
    return 1;
}

int Setting::IsMusicClicked(int x, int y)
{
    if (Objects[MUSIC]->IsClicked(x, y))
        return 1;
    return 0;
}

int Setting::IsSoundClicked(int x, int y)
{
    if (Objects[SOUND]->IsClicked(x, y))
        return 1;
    return 0;
}

void Setting::Destroy()
{
    for (int i = 0; i < Setting::ElementNumber; i++)
    {
        if (Setting::Objects[i])
            delete Setting::Objects[i];
    }
}