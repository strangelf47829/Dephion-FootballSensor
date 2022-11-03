#include <stdio.h>
#include "vectormath.h"
#include "GLDriver.h"
#include "R2D.h"
#include "R3D.h"
#include "Object.h"
#include "Poly.h"
#include "math.h"
#include "Font.h"
#include "string"
#include "string.h"
#include "stdexcept"
#include "terminal.h"
#include "TS2D.h"
#include "FileDriver.h"

#define Width 1000
#define Height 700

terminal term("Test",0,0,64,16);
terminal timm("Bar", 0, 0, 23, 5);
int x = 0;
int xx = 0;

void draw(SDL_Window* window, SDL_Surface* surface, SDL_Renderer* renderer)
{
    //term.Update();
    xx++;
    if(xx == 1)
    {
        xx = 0;
        x++;

        int xxx, y;
        SDL_PumpEvents();
        SDL_GetMouseState(&xxx,&y);
        timm.view->Move(xxx/2,y/2);
        timm.onKey('E');
        timm.onKey(SDLK_RETURN);
    }
    
        
    term.show();
    timm.show();
    term.view->UpdateBorder();
    timm.view->UpdateBorder();
    R2D::d->Render(term.view);
    R2D::d->Render(timm.view);
    //R2D::d->Render(timm.view);
}

void onKeyPressed(SDL_Keycode code)
{
    term.onKey(code);
    timm.view->Move(50,70);
}

int SDL_main(int argc, char *argv[])
{
    char* input = "Hello, World!";
    BBP3FilePage* root = FileDriver::mkDir("C:\\", "root");
    FileDriver::CreateFile("C:\\", root, "YoYo", strlen(input),input);
    R2D::d = new GLDriver(Width,Height);
    R2D::d->init(Width,Height, true, &draw, &onKeyPressed);
}

