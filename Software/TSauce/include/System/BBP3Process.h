#include "Serializeable.h"
#include "TS2D.h"

#ifndef BBP3_PROCESS
#define BBP3_PROCESS


struct SerializedProcess: Serializable
{

};

struct PackedProcess;

class Process
{
    private:
        Process** activeProcesses;

    protected:
        unsigned int PID;
        unsigned long HASH;
        char* Name;
        

        int (*entry)(char**);
        void (*loop)(Process*);
        void (*onKeyPress)(char);
        
        Process();

    public:
        Window* view;
        static Process* Unpack(PackedProcess*);
        Process(char* name, int (*enter)(char**), void (*update)(Process*), void (*key)(char));
        Process(unsigned int w, unsigned int h, char* name, int (*enter)(char**), void (*update)(Process*), void (*key)(char));
        void Update();
        static void UpdateAll();

};


struct PackedProcess
{

};


#endif