#include "RaspIO.c"


#define JAVA_s 0x01





typedef struct JavaFile
{
    struct File codebase;
    int constantPoolCount;
    int interfaceCount;
    int fieldCount;

};