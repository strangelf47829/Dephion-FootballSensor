#include "bmML.c"

typedef void d(int a);

typedef struct Node
{
    d* a;
};


int activator(int a)
{
    return a;
}

int mi(int a)
{

    struct Node nod;
    struct Node* node = &nod;
    node->a = &activator;
    ((d*)node->a)(2);

}
