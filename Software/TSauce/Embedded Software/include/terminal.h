#ifndef TERMINAL_H_
#define TERMINAL_H_
#include "BBP3Process.h"

#define shift(from, to) case from: code = to; break;
class terminal: public Process 
{
    using Process::Process;
    public:
        char* scanf(unsigned int bufferSize, char* prompt);
        void onKey(Sint32 code);
        void show();
        terminal(char* name, unsigned int x, unsigned int y, unsigned int lines, unsigned int active, unsigned int overrun);
        terminal(char* name, unsigned int x, unsigned int y, unsigned int lines, unsigned int active);
        ~terminal();
        
        

    private:
        unsigned int findBufferTo(unsigned int to);
        char** buffer;
        char** tmp;
        unsigned int* len;
        unsigned int* cur;
        unsigned int xP;
        unsigned int yP;
        unsigned int w;
        unsigned int h;
        unsigned int row;
        unsigned int col;
        unsigned int sho;
        unsigned int at;
        int mode;
        unsigned int trueSize;
        unsigned int buffat;
        unsigned int was;
        unsigned int shoAt;
};

#endif