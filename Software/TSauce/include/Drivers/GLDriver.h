#pragma once
#include "C:/mingw_dev_lib/include/SDL2/SDL.h"
#include "TS2D.h"

/*
 * vectormath.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */
#ifndef GLDRIVER_H_
#define GLDRIVER_H_

class GLDriver
{
    
    public:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        void init(int x, int y, bool fullScreen, void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*), void (*keyFunc)(SDL_Keycode));
        GLDriver(int scrWidth, int scrHeight);
        ~GLDriver();
        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Renderer* renderer;
        void RenderFrames(R2D** toDraw, int count);
        void Render(Window* frame);
        void keepAlive(void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*), void (*keyFunc)(SDL_Keycode));
        void (*drawFunc)();
        void Point(int x, int y, R2D* buffer);

};


#endif