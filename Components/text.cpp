
#include "text.hpp"

Text::Text(char *text, char *FontName, int FontSize, int r, int g, int b, int x, int y, int w, int h)
{
    _content = alloc_memory(strlen(text));
    strcpy(_content, text);

    _FontName = alloc_memory(strlen(FontName));
    strcpy(_FontName, FontName);

    _FontSize = FontSize;


    SetColor(&color, r,g,b,255);
    SetRect(&rect, x,y,w,h);
    GetFontSize(_content, _FontName, _FontSize, &rect.w, &rect.h);

}



int Text::Write(SDL_Renderer *render)
{
    return WriteOnScreen(render, _content, rect.x, rect.y, _FontName, _FontSize, color.r, color.g, color.b);
}

Text::~Text()
{
    if (_content != NULL)
        free(_content); _content = NULL;
    if (_FontName != NULL)
        free(_FontName); _FontName = NULL;
}