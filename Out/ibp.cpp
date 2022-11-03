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

#define Width 1000
#define Height 400

obj* cube;
point p = {0,0,0};

point lLL = {-10, -10, 0};
    point lLR = {10, -10, 0};
    point lUL = {-10, 10, 0};
    point lUR = {10, 10,0};

    point uLL = {-10, -10, 20};
    point uLR = {10, -10, 20};
    point uUL = {-10, 10, 20};
    point uUR = {10, 10, 20};
Poly* cubP1 = new Poly(lLR, lUR, lUL);

void draw(SDL_Window* window, SDL_Surface* surface, SDL_Renderer* renderer)
{

    R2D::Stroke(255,255,255);
    /*for(double i = -10; i < 10; i += 0.05){
        double angle = R3D::Camera.angleTo(p);
        double pitch = R3D::Camera.pitchTo(p, {0,0,0}, i);
        R2D::DrawHV(angle,pitch);
    }*/
    R2D::SetCursor(10,20);
    R2D::Text(("fovX: " + std::to_string(R3D::fovX) + "\nfovY: "+ std::to_string(R3D::fovY) + "\nxPos:" + std::to_string(R3D::Camera.x) + "\nyPos:" + std::to_string(R3D::Camera.y)).data());
    R2D::SetCursor(150,20);
    R2D::Stroke(100,100,100);
    try{
        R3D::Render(cube,1);
    }
    catch(const std::exception &e)
    {
        R2D::Stroke(255,0,0);
        R2D::SetCursor(500,20);
        R2D::Text("Exception: "); R2D::Text((char*)e.what());
    }
}

void onKeyPressed(SDL_Keycode code)
{
    switch(code)
    {
        case SDLK_w: R3D::Camera.x += 0.5f; break;
        case SDLK_s: R3D::Camera.x -= 0.5f; break;
        case SDLK_a: R3D::Camera.y += 0.5f; break;
        case SDLK_d: R3D::Camera.y -= 0.5f; break;

        case SDLK_q: R3D::orientation.x += 0.5f; break;
        case SDLK_e: R3D::orientation.x -= 0.5f; break;
        case SDLK_f: R3D::orientation.y += 0.5f; break;
        case SDLK_v: R3D::orientation.y -= 0.5f; break;

        case SDLK_i: R3D::fovX += 0.5f; break;
        case SDLK_o: R3D::fovX -= 0.5f; break;
        case SDLK_k: R3D::fovY += 0.5f; break;
        case SDLK_l: R3D::fovY -= 0.5f; break;

        case SDLK_b: R2D::DEBUG = !R2D::DEBUG; break;
    }
}

int SDL_main(int argc, char *argv[])
{

    

    cube = new obj(8);
    
    PolyOf(cube, 0) = cubP1;
    PolyOf(cube, 1) = new Poly(lUL,lLL,lLR);
    PolyOf(cube, 2) = new Poly(uLR,uUR,uUL);
    PolyOf(cube, 3) = new Poly(uUL,uLL,uLR);


    PolyOf(cube, 4) = new Poly(lLL,uLL,uUL);
    PolyOf(cube, 5) = new Poly(uLL,uLR,lLR);
    PolyOf(cube, 6) = new Poly(lUL,uUL,uLL);
    PolyOf(cube, 7) = new Poly(uUL,uUR,lUR);

    R3D::fovX = 100;
    R3D::fovY = 100;
    R3D::Camera = {-30,0,10};
    R3D::orientation = {0,0,0};
    R2D::TextSize(1);
    R2D::init(Width,Height,false,&draw, &onKeyPressed);

    

}

