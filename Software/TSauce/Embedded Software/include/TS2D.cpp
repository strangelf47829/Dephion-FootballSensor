#include "TS2D.h"
#include "R2D.h"

unsigned int Window::border = 10;
#define WINDOW_BORDER Window::border

Window::Window(unsigned int w, unsigned int h, char* name) : R2D(w+WINDOW_BORDER, h+WINDOW_BORDER+20)
{
    this->x = 0;
    this->y = 0;
    this->name = name;
    this->UpdateBorder();
}

void Window::UpdateBorder()
{
    this->xOffset = 0;
    this->yOffset = 0;
    this->Stroke(255,255,255);
    this->TextSize(1);
    this->SetCursor(2,5);
    this->Text(this->name);
    this->Rect(0,0,this->buffer->width-WINDOW_BORDER,this->buffer->height-WINDOW_BORDER);
    this->Line(0,20,this->buffer->width-WINDOW_BORDER,20);

    this->Stroke(150,150,150);
    
    this->Rectf(this->buffer->width-WINDOW_BORDER+3,WINDOW_BORDER,WINDOW_BORDER-3,this->buffer->height-WINDOW_BORDER);
    this->Rectf(WINDOW_BORDER,this->buffer->height-WINDOW_BORDER+1,this->buffer->width-2*WINDOW_BORDER+3,WINDOW_BORDER-2);
    this->yOffset = 2*WINDOW_BORDER;
    
}
void Window::UpdateBorder(int x, int y)
{
    
    
}
void Window::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Window::Point(unsigned int x, unsigned int y)
{
    d->Point(x+xOffset,y+yOffset,this);
}