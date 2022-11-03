#include "terminal.h"
#include "string"
#include "string.h"
#include "TS2D.h"

#define reroute(a, b) *(*(this->buffer + a) + this->col + 1) = b;
#define getBufPtr(a) *(*(this->buffer + a) + this->col + 1)
#define bitflip(c,a,b) case c: if(mode & b == 0) a = a | b; else a = a ^ b; break;

unsigned int terminal::findBufferTo(unsigned int to)
{
    unsigned int i = 0, last = 0;
    for(int n = 0; n < this->trueSize; n++)
    {
        i = *(*(this->buffer + i) + this->col + 1);
        if(i == to)
            return last;
        last = i;
    }
    return to;
}

void terminal::onKey(Sint32 code)
{
    switch(code)
    {
        case SDLK_RETURN:
        case SDLK_RETURN2:
        //*(*(this->buffer + at)+this->col) = 'n';
        was = at;
        at = *(*(this->buffer + at) + this->col + 1);
        break;
        case SDLK_DELETE:
        case SDLK_BACKSPACE:
        *(*(this->buffer + at)+this->col) = 'n';
        
        
        //int was = at;
        //int then = *(*(this->buffer + at) + this->col + 1);
        if(len[at] != cur[at])
        {
            
            for(unsigned int i = cur[at]; i <= 1+len[at]; i++)
                *(*(this->buffer + at)+i) = *(*(this->buffer + at)+i+1);
        }
        //int now = at;
        
        if(len[at] == 0) 
        {
            if(*(*(this->buffer + findBufferTo(at))+this->col) == 'n')
                at = findBufferTo(at);
            else
            {
                // short the last line with the next
                int next = getBufPtr(at);
                reroute(findBufferTo(at), getBufPtr(at))

                /*
                route the place from
                
                
                */
            }
            
        }
        else { len[at]--; if(code == SDLK_BACKSPACE && cur[at] != 0) cur[at]--; }
        if(cur[at] > len[at])
        cur[at] = len[at];

        break;
        case SDLK_UP: 
        was = findBufferTo(at);
        at = was;
        break;

        case SDLK_DOWN: 
        at = *(*(this->buffer + at) + this->col + 1);
        break;

        case SDLK_LEFT: 
        if(cur[at] == 0)
            at = findBufferTo(at);
        else
        {
            cur[at]--;
            if(cur[at] > len[at])
            {
                cur[at]--;
                at = *(*(this->buffer + at) + this->col + 1);
            }
        }
        break;

        case SDLK_RIGHT: 
        cur[at]++;
        if(cur[at] > len[at])
        {
            cur[at]--;
            at = *(*(this->buffer + at) + this->col + 1);
        }
        break;
        bitflip(SDLK_LCTRL, mode, 2)
        bitflip(SDLK_LSHIFT, mode, 1);

        default:
        #ifndef FONT_LOCAL_SHIFTHANDLER

        
        if(mode)
        {
            if(code >= 'a' && code <= 'z')
                code = code - ('a' - 'A');
            else if(code >= '1' && code <= '5' && code != '2')
                code = code - ('1' - '!');
            else
            switch(code)
            {
                shift('7', '&')
                shift('8', '*')
                shift('9', '(')
                shift('0', ')')
                shift('2', '@')
                shift('6', '^')
                
                shift('-', '_')
                shift('=', '+')
                shift('[', '{')
                shift(']', '}')
                shift('\\', '|')
                shift(';', ':')
                shift('\'', '"')
                shift(',', '<')
                shift('.', '>')
                shift('/', '?')
                shift('`', '~')
            }
        }else
        {
            
        }
        #else
        FONT_LOCAL_SHIFTHANDLER
        #endif
        if(len[at] == this->col)
        {
            buffat++;
            *(*(this->buffer + at)+this->col) = 'y'; 
            int now = at;
            int will = *(*(this->buffer + at) + this->col + 1);
            //toWhatThen -> afterThen
            //now -> then
            //then -> will
            reroute(findBufferTo(buffat), *(*(this->buffer + buffat) + this->col + 1));
            reroute(now, buffat);
            reroute(buffat,will);
            at = buffat;
            
        }
        else
        {
            *(*(this->buffer + at)+cur[at]) = code;
            if(len[at] == cur[at])
                len[at]++;
            cur[at]++;
        }
    }
    
    

}
char* terminal::scanf(unsigned int bufferSize, char* prompt)
{

}
int enter(char** args)
{

}
void loopp(Process* p)
{

}
terminal::terminal(char* name, unsigned int x, unsigned int y, unsigned int lines, unsigned int active) : Process(931, active * 20 + 71, name, &enter, &loopp, (void (*)(char))&onKey)
{
    int bufferLength = 128, overrun = 32;
    this->xP = 0;
    this->yP = 0;
    this->w = 930;
    this->h = active * 20 + 70;
    this->row = bufferLength;
    this->col = 64;
    this->trueSize = bufferLength + overrun;
    this->buffat = bufferLength-1;
    this->shoAt = 0;
    this->sho = active;

    this->len = (unsigned int*)calloc(bufferLength + overrun, sizeof(unsigned int));
    this->cur = (unsigned int*)calloc(bufferLength + overrun, sizeof(unsigned int));
    this->buffer = new char*[bufferLength + overrun];
    
    for(int i = 0; i < bufferLength + overrun; i++)
    {
        *(this->buffer + i) = new char[this->col + 3];
        reroute(i,i+1);
        *(*(this->buffer + i)+this->col) = 'n';
    }
    reroute(bufferLength - 1, 0);
    
}
terminal::terminal(char* name, unsigned int x, unsigned int y, unsigned int lines, unsigned int active, unsigned int overrun) : Process(932, active * 20 + 72, name, &enter, &loopp, (void (*)(char))&onKey)
{
    int bufferLength = 128;
    this->xP = 0;
    this->yP = 0;
    this->w = 930;
    this->h = active * 20 + 70;
    this->row = bufferLength;
    this->col = 64;
    this->trueSize = bufferLength + overrun;
    this->buffat = bufferLength-1;
    this->shoAt = 0;
    this->sho = active;

    this->len = (unsigned int*)calloc(bufferLength + overrun, sizeof(unsigned int));
    this->cur = (unsigned int*)calloc(bufferLength + overrun, sizeof(unsigned int));
    this->buffer = new char*[bufferLength + overrun];
    
    for(int i = 0; i < bufferLength + overrun; i++)
    {
        *(this->buffer + i) = new char[this->col + 3];
        reroute(i,i+1);
        *(*(this->buffer + i)+this->col) = 'n';
    }
    reroute(bufferLength - 1, 0);
    
}

terminal::~terminal(){
    for(int i = 0; i < this->row; i++)
        free(*(this->buffer + i));
    free(this->buffer);
}
void terminal::show()
{
    view->TextSize(1);
    view->SetCursor(2,2);
    view->Stroke(255,255,255);

    view->Line(0,25+(this->sho)*20,w,20+5+(this->sho)*20);
    

    unsigned int addr = (unsigned int)((intptr_t)&buffer);
    //view->Text(("TERMINAL (" + std::to_string(row) + " * " + std::to_string(col) + ") | @ " + std::to_string(addr)).data());
    
    view->Stroke(255,0,0);
    switch(mode)
    {
        case 0b0:
        break;
        case 0b1:
            view->Text(" [CAPS]");
        break;
        case 0b10:
            view->Text(" [CTRL]");
        break;
        case 0b11:
            view->Text(" [CAPS] [CTRL]");
        break;
    }
    view->Stroke(255,255,255);
    //view->Text((" |  next line: " + std::to_string(  *(*(this->buffer + at) + this->col + 1) + 1 )).data());
    //view->Text((" |  size: " + std::to_string( trueSize  )).data());
    //view->Text("\n\n");
    bool cont = false;
    int offset = 0;
    int i = 0;
    for(int k = 0; k < shoAt; k++)
        i = getBufPtr(i);
    view->SetCursor(2,2);//view->SetCursor(2,25);
    //if(shoAt == 0)
    //{
    //    view->Stroke(0,255,0);
    //    //view->Text(" File: [NONE], Size: [NA]");
    //}else
    //{
    //    view->Stroke(255,255,255);
    //    view->Text(" ...");
    //}
    for(int n = 0; n < this->sho; n++)
    {
        char end;
        std::string post;
        std::string pre;
        int length;
        if(n + 1 + offset + shoAt > this->row)
            goto past;
        if(at - offset < shoAt)
        shoAt -= sho;
        if(at > shoAt + sho - 1 + offset && at < row)
        shoAt += sho;
        view->SetCursor(2,5+(n)*20);
        view->Stroke(100,100,100);

        
        
        length = strlen(*(this->buffer + i));
        pre = /*std::to_string(i+1 + offset) + ": "+ */std::to_string((mode & 2 == 0 ? i : n)+1 + offset + shoAt);
        post = *(this->buffer + i);
        end = *(*(this->buffer + i) + this->col);


        
        if(cont)
            { /*view->Stroke(255,0,0);*/pre = "    |";offset--; }
        else
        {
            cont = false;
            if(n + 1 + offset + shoAt >= 10)
            pre += "  |";
            else
            pre += "   |";
        }
        cont = false;
        if(end == 'y')
            cont = true;
        //view->Text(std::to_string(len[i]).data());
        if(i < 128 && i > -1)
        {
        view->Text(pre.data());
        //view->Text(end);

        view->Stroke(255,255,255);
        if(i == at)
            view->Text(post.data(), len[i] - length + (len[at]==cur[at]?1:0), cur[at], '_');
        else
            view->Text(post.data(), len[i] - length);
        }else
        {
            view->Stroke(255,0,0);
            view->Text("[ERR]");
        }


        i = *(*(this->buffer + i) + this->col + 1);
        continue;
        past:
        break;
        
    }
    view->Text('\n');
    view->SetCursor(2,5+(this->sho)*20);
    view->Stroke(255,255,255);
    view->Text(" ...");

}