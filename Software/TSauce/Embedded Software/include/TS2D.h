#include "R2D.h"

#ifndef TS_WINDOW
#define TS_WINDOW

enum WindowMode
{
    show = 0b1,
    drag = 0b10,
    move = 0b100,
    bord = 0b1000
};

class Window: public R2D
{
    private:
        unsigned int x;
        unsigned int y;
        char* name;
        static unsigned int border;
        friend class GLDriver;
        unsigned int xOffset, yOffset;
    public:
        Window(unsigned int x, unsigned int y, char* name);
        void UpdateBorder();
        void UpdateBorder(int x, int y);
        void Move(int x, int y);
        void Point(unsigned int x, unsigned int y) override;


};

#endif