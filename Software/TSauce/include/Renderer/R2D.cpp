
#include "R2D.h"
#include "vectormath.h"
#include "math.h"

int R2D::sr;
int R2D::sg;
int R2D::sb;

Driver* R2D::d;

#define xRes d->SCREEN_WIDTH
#define yRes d->SCREEN_HEIGHT

#define map(input,input_start,input_end,output_start,output_end) output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)


void R2D::Point(int x, int y)
{
    SDL_RenderDrawPoint(R2D::d->renderer, x, y);
}

void R2D::Stroke(int r, int g, int b){
    SDL_SetRenderDrawColor(R2D::d->renderer, r, g, b, 255);
}
void R2D::setDriver(Driver* p)
{
    R2D::d = p;
}
void R2D::init(int x, int y, bool fullScreen, void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*))
{
    R2D::d = new Driver(x, y);
    if(fullScreen)
    {
        
        SDL_SetWindowFullscreen(d->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    }
    d->keepAlive(drawFunc);
}
// swaps two numbers 
void swap(int* a , int*b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
// returns absolute value of number 
float absolute(float x ) 
{ 
    if (x < 0) return -x; 
    else return x; 
} 
  
//returns integer part of a floating point number 
int iPartOfNumber(float x) 
{ 
    return (int)x; 
} 
  
//rounds off a number 
int roundNumber(float x) 
{ 
    return iPartOfNumber(x + 0.5) ; 
} 
  
//returns fractional part of a number 
float fPartOfNumber(float x) 
{ 
    if (x>0) return x - iPartOfNumber(x); 
    else return x - (iPartOfNumber(x)+1); 
  
} 
  
//returns 1 - fractional part of number 
float rfPartOfNumber(float x) 
{ 
    return 1 - fPartOfNumber(x); 
} 
  
// draws a pixel on screen of given brightness 
// 0<=brightness<=1. We can use your own library 
// to draw on screen 
  
void R2D::Line(int x0 , int y0 , int x1 , int y1) 
{ 
    int steep = absolute(y1 - y0) > absolute(x1 - x0) ; 
  
    // swap the co-ordinates if slope > 1 or we 
    // draw backwards 
    if (steep) 
    { 
        swap(&x0 , &y0); 
        swap(&x1 , &y1); 
    } 
    if (x0 > x1) 
    { 
        swap(&x0 ,&x1); 
        swap(&y0 ,&y1); 
    } 
  
    //compute the slope 
    float dx = x1-x0; 
    float dy = y1-y0; 
    float gradient = dy/dx; 
    if (dx == 0.0) 
        gradient = 1; 
  
    int xpxl1 = x0; 
    int xpxl2 = x1; 
    float intersectY = y0; 
  
    // main loop 
    if (steep) 
    { 
        int x; 
        for (x = xpxl1 ; x <=xpxl2 ; x++) 
        { 
            // pixel coverage is determined by fractional 
            // part of y co-ordinate 
            R2D::Point(iPartOfNumber(intersectY),x);
            //drawPixel(iPartOfNumber(intersectY), x, 
            //            rfPartOfNumber(intersectY)); 
            R2D::Point(iPartOfNumber(intersectY)-1,x);
            //drawPixel(iPartOfNumber(intersectY)-1, x, 
            //            fPartOfNumber(intersectY)); 
            intersectY += gradient; 
        } 
    } 
    else
    { 
        int x; 
        for (x = xpxl1 ; x <=xpxl2 ; x++) 
        { 
            // pixel coverage is determined by fractional 
            // part of y co-ordinate 
            R2D::Point(x, iPartOfNumber(intersectY));
            //drawPixel(x, iPartOfNumber(intersectY), 
            //            rfPartOfNumber(intersectY)); 
            R2D::Point(x, iPartOfNumber(intersectY)-1);
            //drawPixel(x, iPartOfNumber(intersectY)-1, 
            //              fPartOfNumber(intersectY)); 
            intersectY += gradient; 
        } 
    } 
  
} 

void R2D::Rect(int x, int y, int w, int h)
{
    Line(x,y,x+w,y);
    Line(x,y,x,y+h);
    Line(x+w,y,x+w,y+h);
    Line(x,y+h,x+w,y+h);
}

void R2D::DrawHV(float h, float v)
{
    int x = floor(map(vector::angleToIndex(h),0,xRes-1,0,d->SCREEN_WIDTH));
    int y = floor(map(vector::pitchToIndex(v),0,yRes-1,0,d->SCREEN_HEIGHT));
    Point(x,y);
}
void R2D::DrawHV(float h1, float v1, float h2, float v2)
{
    int x1 = floor(map(vector::angleToIndex(h1),0,xRes-1,0,d->SCREEN_WIDTH));
    int y1 = floor(map(vector::pitchToIndex(v1),0,yRes-1,0,d->SCREEN_HEIGHT));

    int x2 = floor(map(vector::angleToIndex(h2),0,xRes-1,0,d->SCREEN_WIDTH));
    int y2 = floor(map(vector::pitchToIndex(v2),0,yRes-1,0,d->SCREEN_HEIGHT));
    Line(x1,y1,x2,y2);
}