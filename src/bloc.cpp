
#include <stdio.h>
#include "bloc.hpp"
#include "globals.hpp"

void Bloc::Draw(SDL_Renderer *render, SDL_Rect RectGrid[LINES][COLS])
{
    if (drawable == 1)
    {
        SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(render, &RectGrid[position.l][position.c]);
        SDL_SetRenderDrawColor(render, WHITE_COLOR);
        SDL_RenderDrawRect(render, &RectGrid[position.l][position.c]);
    }
}

void Bloc::Move(int vl, int vc, char grid[LINES][COLS])
{
    if (drawable == 1)
    {
        position.l += vl;
        position.c += vc;
        grid[position.l][position.c] = name;
    }
    
}

void Shape::InitShape(int _l, int _c, int bloc_n, char _name, SDL_Color _color)
{
    l = _l; c = _c;
    bloc_number = bloc_n;
    color = _color;
    disabled = 0;
    rotate_state = 1;
}

void Shape::Draw(SDL_Renderer *render, SDL_Rect GridRect[LINES][COLS], char grid[LINES][COLS])
{
    for (int i = 0; i < bloc_number; i++)
    {
        Blocs[i]->Draw(render, GridRect);
    }
}

void Shape::DrawNextShape(SDL_Renderer *render) {}

void Shape::Init(int l, int c, char grid[LINES][COLS]) {}

void Shape::SetGridShape(int l, int c, char grid[LINES][COLS]) 
{
    
}
void Shape::Rotate(char grid[LINES][COLS]) {}

Shape::~Shape()
{
    
}

void Shape::InitBlocs(char name, int l, int c, SDL_Color _color)
{
    for (int i = 0; i < bloc_number; i++)
    {
        Blocs[i] = new Bloc(name, l, c, _color);
    }
}

void Shape::DelGridShape(char grid[LINES][COLS])
{
    for (int i = 0; i < bloc_number; i++)
    {
        grid[Blocs[i]->GetPos().l][Blocs[i]->GetPos().c] = 'v';
    }
}

int Shape::SetPos(int NewLine, int NewCol, char grid[LINES][COLS])
{
    c = NewLine;
    l = NewCol;
    DelGridShape(grid);
    return 1;
}   


void Shape::Move(int vl, int vc, char grid[LINES][COLS])
{
    if (IsGoodPosition(vl, vc, grid))
    {
        SetPos(l+vl, c+vc, grid);
        for (int i = 0; i < bloc_number; i++)
        {
            Blocs[i]->Move(vl,vc, grid);
        }
    }
        
}

void Shape::MoveDown(Uint64 time, char grid[LINES][COLS], int *newBlocAllowed, int speedTime)
{
    if (time%speedTime >= 0 && time%speedTime <= 60)
    {
        if (!IsDisabled())
        {
            Move(1, 0, grid);
            if (IsDown(grid))
            {
                SetShapeDisabled(1);
                SetShapeDisabledGrid(grid);
                *newBlocAllowed = 1;
            }
        }
        
    }
}

void Shape::SetShapeDisabledGrid(char grid[LINES][COLS])
{
    name = 'b';
    for (int i = 0; i < bloc_number; i++)
    {
        Blocs[i]->SetName(name);
        Blocs[i]->SetDisabled(1);
        grid[Blocs[i]->GetPos().l][Blocs[i]->GetPos().c] = name;
    }
}

int Shape::IsDown(char grid[LINES][COLS])
{
    for (int i = 0; i < bloc_number; i++)
    {   
        if (Blocs[i]->GetPos().l == LINES-1 || grid[Blocs[i]->GetPos().l+1][Blocs[i]->GetPos().c] == 'b')
        {
            return 1;
        }
    }
    return 0;
}

int Shape::IsOut(int l, int c)
{
    if ((l < 0 || l >= LINES) || (c < 0 || c >= COLS))
    {
        return 1;
    }
    return 0;
}

void Shape::MoveRight(char grid[LINES][COLS])
{   
    if (!IsDisabled())
        Move(0, 1, grid);
}

void Shape::MoveLeft(char grid[LINES][COLS])
{   
    if (!IsDisabled())
        Move(0, -1, grid);
}

int Shape::IsGoodPosition(int vl, int vc, char grid[LINES][COLS])
{
    int l_temp, c_temp;
    for (int i = 0; i < bloc_number; i++)
    {
        l_temp = Blocs[i]->GetPos().l;
        c_temp = Blocs[i]->GetPos().c;
        if (!IsEmptyGridPlace(l_temp+vl, c_temp+vc, name, grid)
        || IsOut(l_temp+vl, c_temp+vc))
        {
            return 0;
        }
    }
    return 1;
}


void Shape::DisableGridShape(char grid[LINES][COLS]) {}

void Shape::DelSubShapes(int line_number, char grid[LINES][COLS])
{
    for (int i = 0; i < bloc_number; i++)
    {
        if (Blocs[i]->GetPos().l == line_number)
        {
            Blocs[i]->SetDrawable(0);
        } 
        else if (Blocs[i]->GetPos().l < line_number)
        {
            Blocs[i]->Move(1, 0, grid);
        }
    }
}
// SECTION : SQUARE ====================================================================================


void Square::Init(int l, int c, char grid[LINES][COLS]) 
{
    SDL_Color _color = {255,255,0,255};
    bloc_number = 4;
    name = 'c';
    InitShape(l, c, bloc_number, name, _color);
    InitBlocs(name, l, c, _color);
    SetGridShape(l, c, grid);
}

void Square::SetGridShape(int l, int c, char grid[LINES][COLS]) 
{
    Pos blocs_positions[4] = {{l, c}, {l+1, c}, {l, c+1}, {l+1, c+1}};
    for (int i = 0; i < bloc_number; i++)
    {
        if (IsOut(blocs_positions[i].l, blocs_positions[i].c) || 
        !IsEmptyGridPlace(blocs_positions[i].l, blocs_positions[i].c, name, grid))
            return;
    }

    for (int i = 0; i < bloc_number; i++)
    {
        SetGridName(blocs_positions[i].l, blocs_positions[i].c, name, grid);
        Blocs[i]->SetPos(blocs_positions[i].l, blocs_positions[i].c);
    }
}

void Square::DrawNextShape(SDL_Renderer *render)
{
    SDL_Rect rects[4];
    SDL_Rect rect = {0,0,50,50};
    SDL_Color _color = {255, 255, 0, 255};

    rect.x = NEXTSHAPE_SPACE_X+38; rect.y = NEXTSHAPE_SPACE_Y + 38;
    rects[0] = rect;
    rect.x = NEXTSHAPE_SPACE_X+38 + rect.w; rect.y = NEXTSHAPE_SPACE_Y + 38;
    rects[1] = rect;
    rect.x = NEXTSHAPE_SPACE_X+38; rect.y = NEXTSHAPE_SPACE_Y + 38 + rect.h;
    rects[2] = rect;
    rect.x = NEXTSHAPE_SPACE_X+38 + rect.w; rect.y = NEXTSHAPE_SPACE_Y + 38 + rect.h;
    rects[3] = rect;

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(render, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(render, &rects[i]);
        SDL_SetRenderDrawColor(render, WHITE_COLOR);
        SDL_RenderDrawRect(render, &rects[i]);
    }
}
// SECTION : LINE ======================================================================================

void Line::Init(int l, int c, char grid[LINES][COLS]) 
{
    SDL_Color _color = {0,255,255,255};
    name = 'l';
    disabled = 0;
    InitShape(l, c, 4, name, _color);
    InitBlocs(name, l, c, _color);
    SetGridShape(l, c, grid);
}

void Line::SetGridShape(int l, int c, char grid[LINES][COLS])
{
    Pos blocs_positions[4];
    if (rotate_state == 1)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l, c+1};
        blocs_positions[2] = {l, c+2}; blocs_positions[3] = {l, c+3};
        
    }
    else if (rotate_state == 2)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l+2, c}; blocs_positions[3] = {l+3, c};
    }
    for (int i = 0; i < bloc_number; i++)
    {
        if (IsOut(blocs_positions[i].l, blocs_positions[i].c) || 
        !IsEmptyGridPlace(blocs_positions[i].l, blocs_positions[i].c, name, grid))
            return;
    }
    for (int i = 0; i < bloc_number; i++)
    {
        SetGridName(blocs_positions[i].l, blocs_positions[i].c, name, grid);
        Blocs[i]->SetPos(blocs_positions[i].l, blocs_positions[i].c);
    }
}

void Line::Rotate(char grid[LINES][COLS])
{
    int _l = Blocs[0]->GetPos().l;
    int _c = Blocs[0]->GetPos().c;
    
    if (!IsDisabled())
    {
        DelGridShape(grid);
        if (rotate_state == 1)
        {
            rotate_state = 2;
            SetPos(l-3, c+2, grid);
            SetGridShape(_l-3, _c+2, grid);
        }
        else if (rotate_state == 2)
        {
            rotate_state = 1;
            SetPos(l+3, c-2, grid);
            SetGridShape(_l+3, _c-2, grid);
        }
    }
    
}

void Line::DrawNextShape(SDL_Renderer *render)
{
    SDL_Rect rects[4];
    SDL_Rect rect = {0,0,30,30};
    SDL_Color _color = {0,255,255,255}; 

    rect.x = NEXTSHAPE_SPACE_X+(NEXTSHAPE_SPACE_SIZE-rect.w*4)/2; rect.y = NEXTSHAPE_SPACE_Y + (NEXTSHAPE_SPACE_SIZE-rect.h)/2;
    rects[0] = rect;
    rect.x += rect.w;
    rects[1] = rect;
    rect.x += rect.w; 
    rects[2] = rect;
    rect.x += rect.w;
    rects[3] = rect;

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(render, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(render, &rects[i]);
        SDL_SetRenderDrawColor(render, WHITE_COLOR);
        SDL_RenderDrawRect(render, &rects[i]);
    }
}

// SECTION : STAIR ======================================================================================

void Stair::Init(int l, int c, char grid[LINES][COLS]) 
{
    SDL_Color _color = {0,255,0,255};
    name = 's';
    InitShape(l, c, 4, name, _color);
    InitBlocs(name, l, c, _color);
    SetGridShape(l, c, grid);
}

void Stair::SetGridShape(int l, int c, char grid[LINES][COLS])
{
    Pos blocs_positions[4];
    if (rotate_state == 1)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l+1, c+1}; blocs_positions[3] = {l+2, c+1};
    }
    else if (rotate_state == 2)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l, c-1};
        blocs_positions[2] = {l+1, c-1}; blocs_positions[3] = {l+1, c-2};
    }
    for (int i = 0; i < bloc_number; i++)
    {
        if (IsOut(blocs_positions[i].l, blocs_positions[i].c) || 
        !IsEmptyGridPlace(blocs_positions[i].l, blocs_positions[i].c, name, grid))
            return;
    }
    for (int i = 0; i < bloc_number; i++)
    {
        SetGridName(blocs_positions[i].l, blocs_positions[i].c, name, grid);
        Blocs[i]->SetPos(blocs_positions[i].l, blocs_positions[i].c);
    }
    
}

void Stair::Rotate(char grid[LINES][COLS])
{
    int _l = Blocs[0]->GetPos().l;
    int _c = Blocs[0]->GetPos().c;
    
    if (!IsDisabled())
    {
        DelGridShape(grid);
        if (rotate_state == 1)
        {
            rotate_state = 2;
            SetPos(_l, _c+1, grid);
            SetGridShape(_l, _c+1, grid);
        }
        else if (rotate_state == 2)
        {
            rotate_state = 1;
            SetPos(_l, _c-1, grid);
            SetGridShape(_l, _c-1, grid);
        }
    }
    
}

void Stair::DrawNextShape(SDL_Renderer *render)
{
    SDL_Rect rects[4];
    SDL_Rect rect = {0,0,40,40};
    SDL_Color _color = {0,255,0,255};

    rect.x = NEXTSHAPE_SPACE_X+(NEXTSHAPE_SPACE_SIZE-rect.w*2)/2; rect.y = NEXTSHAPE_SPACE_Y + (NEXTSHAPE_SPACE_SIZE-rect.h*3)/2;
    rects[0] = rect;
    rect.y += rect.h;
    rects[1] = rect;
    rect.x += rect.w; 
    rects[2] = rect;
    rect.y += rect.h;
    rects[3] = rect;

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(render, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(render, &rects[i]);
        SDL_SetRenderDrawColor(render, WHITE_COLOR);
        SDL_RenderDrawRect(render, &rects[i]);
    }
}


// SECTION : Foot ======================================================================================

void Foot::Init(int l, int c, char grid[LINES][COLS]) 
{
    SDL_Color _color = {255,128,0,255};
    name = 'f';
    InitShape(l, c, 4, name, _color);
    InitBlocs(name, l, c, _color);
    SetGridShape(l, c, grid);
}

void Foot::SetGridShape(int l, int c, char grid[LINES][COLS])
{
    Pos blocs_positions[4];
    if (rotate_state == 1)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l+2, c}; blocs_positions[3] = {l+2, c+1};
    }
    else if (rotate_state == 2)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l, c+1}; blocs_positions[3] = {l, c+2};
    }
    else if (rotate_state == 3)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l, c+1};
        blocs_positions[2] = {l+1, c+1}; blocs_positions[3] = {l+2, c+1};
    }
    else if (rotate_state == 4)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l+1, c-1}; blocs_positions[3] = {l+1, c-2};
    }
    for (int i = 0; i < bloc_number; i++)
    {
        if (IsOut(blocs_positions[i].l, blocs_positions[i].c) || 
        !IsEmptyGridPlace(blocs_positions[i].l, blocs_positions[i].c, name, grid))
            return;
    }
    for (int i = 0; i < bloc_number; i++)
    {
        SetGridName(blocs_positions[i].l, blocs_positions[i].c, name, grid);
        Blocs[i]->SetPos(blocs_positions[i].l, blocs_positions[i].c);
    }
}

void Foot::Rotate(char grid[LINES][COLS])
{
    int _l = Blocs[0]->GetPos().l;
    int _c = Blocs[0]->GetPos().c;
    
    if (!IsDisabled())
    {
        DelGridShape(grid);
        if (rotate_state == 1)
        {
            rotate_state = 2;
            SetPos(_l+1, _c-1, grid);
            SetGridShape(_l+1, _c-1, grid);
        }
        else if (rotate_state == 2)
        {
            rotate_state = 3;
            SetPos(_l-1, _c, grid);
            SetGridShape(_l-1, _c, grid);
        }
        else if (rotate_state == 3)
        {
            rotate_state = 4;
            SetPos(_l, _c+2, grid);
            SetGridShape(_l, _c+2, grid);
        } 
        else if (rotate_state == 4)
        {
            rotate_state = 1;
            SetPos(_l, _c-1, grid);
            SetGridShape(_l, _c-1, grid);
        }
    }
}

void Foot::DrawNextShape(SDL_Renderer *render)
{
    SDL_Rect rects[4];
    SDL_Rect rect = {0,0,40,40};
    SDL_Color _color = {255,128,0,255};

    rect.x = NEXTSHAPE_SPACE_X+(NEXTSHAPE_SPACE_SIZE-rect.w*2)/2; rect.y = NEXTSHAPE_SPACE_Y + (NEXTSHAPE_SPACE_SIZE-rect.h*3)/2;
    rects[0] = rect;
    rect.y += rect.h;
    rects[1] = rect;
    rect.y += rect.h; 
    rects[2] = rect;
    rect.x += rect.w;
    rects[3] = rect;

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(render, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(render, &rects[i]);
        SDL_SetRenderDrawColor(render, WHITE_COLOR);
        SDL_RenderDrawRect(render, &rects[i]);
    }
}

// SECTION : Pyramid ======================================================================================

void Pyramid::Init(int l, int c, char grid[LINES][COLS]) 
{
    SDL_Color _color = {255,0,127,255};
    name = 'p';
    InitShape(l, c, 4, name, _color);
    InitBlocs(name, l, c, _color);
    SetGridShape(l, c, grid);
}

void Pyramid::SetGridShape(int l, int c, char grid[LINES][COLS])
{
    Pos blocs_positions[4];
    if (rotate_state == 1)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c-1};
        blocs_positions[2] = {l+1, c}; blocs_positions[3] = {l+1, c+1};
    }
    else if (rotate_state == 2)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l+1, c+1}; blocs_positions[3] = {l+2, c};
    }
    else if (rotate_state == 3)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l, c+1};
        blocs_positions[2] = {l+1, c+1}; blocs_positions[3] = {l, c+2};
    }
    else if (rotate_state == 4)
    {
        blocs_positions[0] = {l, c}; blocs_positions[1] = {l+1, c};
        blocs_positions[2] = {l+1, c-1}; blocs_positions[3] = {l+2, c};
    }

    for (int i = 0; i < bloc_number; i++)
    {
        if (IsOut(blocs_positions[i].l, blocs_positions[i].c) || 
        !IsEmptyGridPlace(blocs_positions[i].l, blocs_positions[i].c, name, grid))
            return;
    }
    for (int i = 0; i < bloc_number; i++)
    {
        SetGridName(blocs_positions[i].l, blocs_positions[i].c, name, grid);
        Blocs[i]->SetPos(blocs_positions[i].l, blocs_positions[i].c);
    }
}

void Pyramid::Rotate(char grid[LINES][COLS])
{
    int _l = Blocs[0]->GetPos().l;
    int _c = Blocs[0]->GetPos().c;
    
    if (!IsDisabled())
    {
        DelGridShape(grid);
        if (rotate_state == 1)
        {
            rotate_state = 2;
            SetPos(_l, _c, grid);
            SetGridShape(_l, _c, grid);
        }
        else if (rotate_state == 2)
        {
            rotate_state = 3;
            SetPos(_l+1, _c-1, grid);
            SetGridShape(_l+1, _c-1, grid);
        }
        else if (rotate_state == 3)
        {
            rotate_state = 4;
            SetPos(_l-1, _c+1, grid);
            SetGridShape(_l-1, _c+1, grid);
        } 
        else if (rotate_state == 4)
        {
            rotate_state = 1;
            SetPos(_l, _c, grid);
            SetGridShape(_l, _c, grid);
        }
    }
}

void Pyramid::DrawNextShape(SDL_Renderer *render)
{
    SDL_Rect rects[4];
    SDL_Rect rect = {0,0,40,40};
    SDL_Color _color = {255,0,127,255};

    rect.x = NEXTSHAPE_SPACE_X + (NEXTSHAPE_SPACE_SIZE-rect.w*2)/2; rect.y = NEXTSHAPE_SPACE_Y + (NEXTSHAPE_SPACE_SIZE-rect.h*2)/2;
    rects[0] = rect;
    rect.y += rect.h; rect.x -= rect.w;
    rects[1] = rect;
    rect.x += rect.w;
    rects[2] = rect;
    rect.x += rect.w;
    rects[3] = rect;

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(render, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(render, &rects[i]);
        SDL_SetRenderDrawColor(render, WHITE_COLOR);
        SDL_RenderDrawRect(render, &rects[i]);
    }
}