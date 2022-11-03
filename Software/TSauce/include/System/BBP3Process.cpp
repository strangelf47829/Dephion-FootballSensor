#include "BBP3Process.h"

Process::Process(){}

Process::Process(char* name, int (*enter)(char**), void (*update)(Process*), void (*key)(char))
{
    view = new Window(20,20, name);
    //view->UpdateBorder();


}

Process::Process(unsigned int w, unsigned int h, char* name, int (*enter)(char**), void (*update)(Process*), void (*key)(char))
{
    view = new Window(w,h, name);
    //view->UpdateBorder();


}

void Process::Update()
{
    loop(this);
}