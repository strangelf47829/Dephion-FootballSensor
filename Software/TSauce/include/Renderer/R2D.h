#include "GLDriver.h"

#ifndef R2D_H_
#define R2D_H_


class R2D
{
    private:
        
        static int sr;
        static int sg;
        static int sb;
    public:
        static Driver* d;
        static void setDriver(Driver* d);
        static void Point(int x, int y);
        static void Stroke(int r, int g, int b);
        static void init(int x, int y, bool fullscreen, void (*drawFunc)(SDL_Window*, SDL_Surface*, SDL_Renderer*));
        static void Line(int x1, int y1, int x2, int y2);
        static void Rect(int x1, int y1, int w, int h);
        static void Tri(int x1, int y1, int x2, int y2, int x3, int y3);
        static void DrawHV(float h, float v);
        static void DrawHV(float h1, float v1, float h2, float v2);
};

#endif
