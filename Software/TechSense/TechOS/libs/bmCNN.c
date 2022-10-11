#include <stdio.h>

typedef int layerFunc(int a);

struct layer
{
    //The amount of x pixels in the layer
    unsigned int xRes;

    //The amount of y pixels in the layer
    unsigned int yRes;

    //The previous layer (itself if none)
    struct layer** previous;
    int previousCount;

    //The next layer (itself if none)
    struct layer** next;
    int nextCount;

    //The pixel values
    unsigned char pixels[0xFFFFFFFF];

    layerFunc* layerFunction;

};


struct layer first;
struct layer second;



void setPixelOf(struct layer l, int x, int y, int to)
{
    *(l.pixels + x + l.yRes * y) = to;
}
int getPixelOf(struct layer l, int x, int y)
{
    return *(l.pixels + x + l.yRes * y);
}


void printMatrix(struct layer a)
{
    printf("Hello, World!");
    for(int x = 0; x < a.xRes; x++)
    {   
        for(int y = 0; y < a.yRes; y++)
        {
            printf(" (%d, %d): %d", x, y, getPixelOf(a, x, y));


        }
    }
}
int main()
{
    first.xRes = 20;
    first.yRes = 20;
    setPixelOf(first, 10, 10, 255);
    printMatrix(first);
    return 0;
}