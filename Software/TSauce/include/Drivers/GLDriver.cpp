#include "GLDriver.h"
#include <stdio.h>

Driver::Driver(int x, int y)
{
    this->SCREEN_HEIGHT = y;
    this->SCREEN_WIDTH = x;
    

    //The window we'll be rendering to
    this->window = NULL;
    
    //The surface contained by the window
    this->screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&window, &renderer );
        //window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );
            

            //Update the surface
            SDL_UpdateWindowSurface( window );

            
            

            //Hack to get window to stay up
            
        }
    }
    //Destroy window
    
}

Driver::~Driver()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

void Driver::keepAlive(void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*))
{
SDL_Event e; 
            bool quit = false; 
            while( quit == false )
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
                drawFunc(this->window, this->screenSurface, this->renderer);
                
                SDL_RenderPresent(renderer);
                //SDL_UpdateWindowSurface(this->window);
                while( SDL_PollEvent( &e ) )
                {
                    if( e.type == SDL_QUIT ) 
                        quit = true; 
                    
                }
            }
}

