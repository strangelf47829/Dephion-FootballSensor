#include "R2D.h"
#include "vectormath.h"
#include "math.h"
#include "Font.h"
#include "string"
#include "string.h"
#include "R3D.h"
#include "TS2D.h"
#include "GLDriver.h"


GLDriver* R2D::d;

#define xRes d->SCREEN_WIDTH
#define yRes d->SCREEN_HEIGHT

#define map(input,input_start,input_end,output_start,output_end) output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)


R2D::R2D(unsigned int w, unsigned int h)
{
    this->buffer = new R2DBuffer();
    this->buffer->height = h;
    this->buffer->width = w;
    sr = 0;
    sg = 0;
    sb = 0;
    
    this->buffer->Location = (Pixel**)calloc(w * h, sizeof(Pixel*));
    for(int n = 0; n < w * h; n++)
        *(this->buffer->Location + n) = new Pixel({0,0,0});
}


void R2D::Stroke(int r, int g, int b){
    sr = r;
    sg = g;
    sb = b;

}

void R2D::Point(unsigned int x, unsigned int y)
{
    d->Point(x,y,this);
    //*(this->buffer->Location + x) = new Pixel({sr,sg,sb});
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
  
void R2D::Line(int X0 , int Y0 , int X1 , int Y1) 
{ 
    int x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
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
            Point(iPartOfNumber(intersectY),x);
            //drawPixel(iPartOfNumber(intersectY), x, 
            //            rfPartOfNumber(intersectY)); 
            //Point(iPartOfNumber(intersectY)-1,x);
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
            Point(x, iPartOfNumber(intersectY));
            //drawPixel(x, iPartOfNumber(intersectY), 
            //            rfPartOfNumber(intersectY)); 
            // Point(x, iPartOfNumber(intersectY)-1);
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
void R2D::Rectf(int x, int y, int w, int h)
{
    for(int xx = x; xx <= x + w; xx++)
        Line(xx,y,xx,y+h);
}

void R2D::DrawHV(float h, float v, R3D* renderer)
{
    int x = floor(map(vector::angleToIndex(h, renderer->fovX),0,xRes-1,0,d->SCREEN_WIDTH));
    int y = floor(map(vector::pitchToIndex(v, renderer->fovX),0,yRes-1,0,d->SCREEN_HEIGHT));
    //if(R2D::DEBUG)
    d->Point(h,v, this);
}
void R2D::DrawHV(float h1, float v1, float h2, float v2, R3D* renderer)
{
    
    R2D::Text("\n");
    precision a1 = vector::angleToIndex(h1, renderer->fovX);
    precision p1 = vector::pitchToIndex(v1, renderer->fovX);
    precision a2 = vector::angleToIndex(h2, renderer->fovX);
    precision p2 = vector::pitchToIndex(v2, renderer->fovX);
    R2D::Text((
        "\ta1: " + std::to_string(a1) + "\n" +
        "\tp1: " + std::to_string(p1) + "\n" +
        "\ta2: " + std::to_string(a2) + "\n" +
        "\tp2: " + std::to_string(p2) + "\n"
    ).data());
    int x1 = floor(map(a1,0,renderer->fovX,0,d->SCREEN_WIDTH));
    int y1 = floor(map(p1,0,renderer->fovY,0,d->SCREEN_HEIGHT));

    int x2 = floor(map(a2,0,renderer->fovX,0,d->SCREEN_WIDTH));
    int y2 = floor(map(p2,0,renderer->fovY,0,d->SCREEN_HEIGHT));
    R2D::Text((
        "\tX1: " + std::to_string(x1) + "\n" +
        "\tY1: " + std::to_string(y1) + "\n" +
        "\tX2: " + std::to_string(x2) + "\n" +
        "\tY2: " + std::to_string(y2) + "\n"
    ).data());
}
void R2D::TextSize(int size)
{
    R2D::text = size;
}
void R2D::SetCursor(int x, int y)
{
    tx = x; rcx = x; ty = y;
}
void R2D::Mask(long long mask)
{
    int k = 0;
    mask = mask;
    if(text == 1)
    {
        for(int i = 0; true; i++)
        {

            if(i == 8)
            {
                k++; i = 0;
                if(k == 8)
                    break;
            }

            bool p = mask & 1;
            mask = mask >> 1;
            if(p)
                Point(tx+(8-k)*text,ty+i*text);
        }
    }else
    {
        for(int i = 0; true; i++)
        {
            
            if(i == 8)
            {
                k++; i = 0;
                if(k == 8)
                    break;
            }
            
            bool p = mask & 1;
            mask = mask >> 1;
            if(p)
                for(int xx = tx; xx < tx + text; xx++)
                    for(int yy = ty; yy < ty + text; yy++)
                        Point(xx+(8-i)*text,yy+(8-k)*text);
        }
    }
    
    tx += text;
}


void R2D::Text(char* str)
{
    R2D::Text(str, 0);
}
void R2D::Text(char* str, int offset)
{
    int len = strlen(str);
    for(int i = 0; i < len + offset; i++)
    {
        Text(*(str+i*sizeof(char)));
        tx += text*8;
    }
}
void R2D::Text(char* str, int offset, int cursor, char replacement)
{
    int len = strlen(str);
    for(int i = 0; i < len + offset; i++)
    {
        if(i == cursor)
            Text(replacement);
        else
            Text(*(str+i*sizeof(char)));
        tx += text*8;
    }
}
void R2D::Text(char chr)
{
    INTFONTARR
    long long mask = fontArray[chr];
    //long long mask = BBP3FONT_ERR;
    switch(chr)
    {
        case ' ':
            mask = 0;
            break;
        case '\n':
            tx = rcx;
            ty += 20;
            goto skip;
        case '\t':
            mask = 0;
            tx += 3 * text;
        break;
    }
    R2D::Mask(mask);
  skip:
    return;
}
