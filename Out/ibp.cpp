#include <stdio.h>
#include "vectormath.h"
#include "GLDriver.h"
#include "R2D.h"
#include "R3D.h"
#include "Object.h"
#include "Poly.h"
#include "math.h"

//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

#define PI 3.1415

float a = 0;
obj* cube;

void draw(SDL_Window* window, SDL_Surface* surface, SDL_Renderer* renderer)
{
    for(int i = 0; i < 4424230; i++)
    {
        
    }
    R2D::Stroke(50,50,50);
    R2D::Line(0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2);
    R2D::Line(SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
    R2D::Stroke(0,255,0);
    R3D::Render(cube);

    a += 0.01f;
    R3D::Camera.x = -30 * cos(a);
    R3D::Camera.y = -30 * sin(a);
    R3D::orientation.y = (180/PI)*a;
    if(a > PI)
        a = 0;
    
}

int SDL_main(int argc, char *argv[])
{
    point lLL = {-10, -10, 0};
    point lLR = {10, -10, 0};
    point lUL = {-10, 10, 0};
    point lUR = {10, 10, 0};

    point uLL = {-10, -10, 20};
    point uLR = {10, -10, 20};
    point uUL = {-10, 10, 20};
    point uUR = {10, 10, 20};

    cube = new obj(8);
    
    PolyOf(cube, 0) = new Poly(lLR,lUR,lUL);
    PolyOf(cube, 1) = new Poly(lUL,lLL,lLR);
    PolyOf(cube, 2) = new Poly(uLR,uUR,uUL);
    PolyOf(cube, 3) = new Poly(uUL,uLL,uLR);


    PolyOf(cube, 4) = new Poly(lLL,uLL,uUL);
    PolyOf(cube, 5) = new Poly(uLL,uLR,lLR);
    PolyOf(cube, 6) = new Poly(lUL,uUL,uLL);
    PolyOf(cube, 7) = new Poly(uUL,uUR,lUR);

    R3D::fovX = 180;
    R3D::fovY = 180;
    R3D::Camera = {-30,0,10};
    R3D::orientation = {0,0,0};

    R2D::init(SCREEN_WIDTH,SCREEN_HEIGHT,false, &draw);
    
    return 0;
}