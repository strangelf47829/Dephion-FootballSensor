
#include "GLDriver.h"
#include "R3D.h"

#ifndef R2D_H_
#define R2D_H_

typedef int pixelResolution;
#define GetPixel(x,y) *(this->buffer->Location + x + this->buffer->height * y)
#define SetPixel(x,y,r,g,b) GetPixel(x,y) = {r,g,b}

struct Pixel
{
    pixelResolution r;
    pixelResolution g;
    pixelResolution b;
};

class GLDriver;

struct R2DBuffer
{
    Pixel** Location;
    unsigned int width;
    unsigned int height;
    bool refresh = true;
};

class R2D
{

    private:
        int sr;   //Stroke red
        int sg;   //Stroke Green
        int sb;   //Stroke Blue
        int text; //Return to this when new line
        int tx;   //Cursor x
        int ty;   //Cursor y
        int rcx;  //??

        int width;
        int height;
        
        R2DBuffer* buffer;
        
        friend class GLDriver;
        friend class Window;

    public:
        R2D(unsigned int width, unsigned int height);
        static GLDriver* d; //The driver to render to
        friend class GLDriver;
        virtual void Point(unsigned int x, unsigned int y);
        void Stroke(int r, int g, int b);void Line(int x1, int y1, int x2, int y2);
        void Rect(int x1, int y1, int w, int h);
        void Rectf(int x1, int y1, int w, int h);
        void Tri(int x1, int y1, int x2, int y2, int x3, int y3);
        void DrawHV(float h, float v, R3D* renderer);
        void DrawHV(float h1, float v1, float h2, float v2, R3D* renderer);
        void TextSize(int size);
        
        void SetCursor(int x, int y);
        void Mask(long long mask);
        void Text(char* str);
        void Text(char* str, int offset);
        void Text(char* str, int offset, int cursor, char replacement);
        void Text(int num);
        void Text(char chr);
        


};


#endif
