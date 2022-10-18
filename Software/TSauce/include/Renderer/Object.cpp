#include "Object.h"
#include "cstdlib"
#include "Poly.h"

obj::obj(int count) : transform(vector(0,0,0)), polyCount(count)
{
    this->poly = (Poly**)malloc((count)*sizeof(*(this->poly)));
    for(int i = 0; i < count; i++)
    {
        Poly* p = new Poly({10,0,0},{10,10,0},{10,10,5});
        *(this->poly+sizeof(Poly*) * i) = p;
    } 

}

obj::~obj()
{
    free(this->poly);
}