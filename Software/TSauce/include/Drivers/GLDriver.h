/*
 * vectormath.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */
#ifndef GLDRIVER_H_
#define GLDRIVER_H_

#ifndef SDL_h_
#include "C:/mingw_dev_lib/include/SDL2/SDL.h"
#endif

class Driver
{
    private:
    
    public:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        Driver(int scrWidth, int scrHeight);
        ~Driver();
        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Renderer* renderer;
        void keepAlive(void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*));
        void (*drawFunc)();

};


#endif