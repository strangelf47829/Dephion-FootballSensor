///c/Users/stran/Documents/One Blast/OneBlast Products/Contracts/Dephion/Football Table Sensor/Dephion-FootballSensor/Software/Embedded software/Video/User
#include "Poly.h"
#include "object.h"
#include "driver.h"
#include "vectormath.h"
#include "stdio.h"

unsigned int xRes = 600;
unsigned int yRes = 400;

unsigned short fovX = 90;
unsigned short fovY = 50;

vector cameraPosition;
vector cameraDirection;

unsigned int cullNear = 10;
unsigned int cullFar = 500;

struct timing x = {1,2,2,2};
struct timing y = {1,2,2,2};

driver d();

//List: current objects

int main()
{
	printf("Hello, World!");
	printf("\n");
}

void me()
{
	

}





