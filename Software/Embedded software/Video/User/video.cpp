
#include "Poly.h"
#include "object.h"
#include "driver.h"

unsigned int xRes = 600;
unsigned int yRes = 400;

unsigned short fovX = 90;
unsigned short fovY = 50;

typedef point vector;

vector cameraPosition;
vector cameraDirection;

unsigned int cullNear = 10;
unsigned int cullFar = 500;



struct point
{
	double x;
	double y;
	double z;
};

struct line
{
	point a;
	point b;
};


//List: current objects

driver d(2,2);

void me()
{
	d.setPixel();

}





