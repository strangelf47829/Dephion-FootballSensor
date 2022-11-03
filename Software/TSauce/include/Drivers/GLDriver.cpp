#include "GLDriver.h"
#include "R2D.h"
#include "TS2D.h"
#include <stdio.h>

GLDriver::GLDriver(int x, int y)
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

GLDriver::~GLDriver()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

void GLDriver::keepAlive(void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*), void (*keyFunc)(SDL_Keycode))
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
                    switch(e.type)
                    {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_KEYDOWN:
                            keyFunc(e.key.keysym.sym);
                            break;
                    }
                    
                }
            }
}

void GLDriver::init(int x, int y, bool fullScreen, void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*), void (*keyFunc)(SDL_Keycode))
{
    if(fullScreen)
    {
        
        SDL_SetWindowFullscreen(R2D::d->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    }
    R2D::d->keepAlive(drawFunc,keyFunc);
}

void GLDriver::Point(int x, int y, R2D* buffer)
{
    if(x < buffer->buffer->width && y < buffer->buffer->height)
    *(buffer->buffer->Location + (x + y * buffer->buffer->width)) = new Pixel({buffer->sr,buffer->sg,buffer->sb});
}

void GLDriver::RenderFrames(R2D** toDraw, int count)
{

}
void GLDriver::Render(Window* frame)
{
    Pixel** location = frame->buffer->Location;
    int w = frame->buffer->width;
    int h = frame->buffer->height;
    int x = frame->x + frame->x;
    int y = frame->y + frame->y;
    for(int n = 0, xx = x, yy = y; n < (w) * (h); n++)
    {
        
        SDL_SetRenderDrawColor(renderer, (*location)->r, (*location)->g, (*location)->b,255);
        SDL_RenderDrawPoint(renderer, xx, yy);
        if(frame->buffer->refresh && !( (h-yy < Window::border) || (yy-y < 2*Window::border) || (w-xx < Window::border) ))
            (*location) = new Pixel({0,0,0});
        xx++;
        if(xx == x + w + 0)
        {
            yy++;
            xx = x;
        }
        location++;
    }

    
}