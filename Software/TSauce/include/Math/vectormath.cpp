#include "vectormath.h"
#include <cmath>
#include <stdio.h>
#include "R3D.h"
#include "R2D.h"
#include "string"
#include "string.h"

#define xRes R2D::d->SCREEN_WIDTH
#define yRes R2D::d->SCREEN_HEIGHT


#define map(input,input_start,input_end,output_start,output_end) output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)

#define PI 3.1415



vector::vector(dimension a, dimension b, dimension c)
{
    printf("Made with %Lf \n", a);
    this->x = a;
    this->y = b;
    this->z = c;
    printf("Constructor equals %Lf \n", x);
}


int clampInt(int mn, int t, int mx)
{
  return __max(__min(t, mx), mn);
}

int vector::angleToIndex(precision angle, precision fovX)
{
  precision t = angleToViewportLerp(angle,fovX)*xRes;
  //R2D::Text(("angle t: " + std::to_string(t) + "\n").data());
  //return clampInt(0, roundf(t), xRes-1);
  return roundf(t);
}
int vector::pitchToIndex(precision angle, precision fovY)
{
  //R2D::Text(("pitch: " + std::to_string(angle) + "\n").data());
  precision t = map(angle, -fovY/2.0, fovY/2.0, yRes, 0);
  //R2D::Text(("\t\tt: " + std::to_string(t) + "(" + std::to_string(fovY) + ")\n").data());
  //return clampInt(0, roundf(t), yRes-1);
  return roundf(t);
}

precision vector::minAngle(precision a, precision b, precision c, precision d)
{
  int ind = 0;
  d = c;
  precision angles[] = {a,b,c,d};
  precision adj[] = {a,b,c,d};
  for (int i = 0; i < 4; i++) //Correct negative underflow angles, and positive overflow angles
    adj[i] = angles[i] < -180 ? angles[i] + 360 : (angles[i] > 180 ? angles[i] - 360 : angles[i]);
  for (int i = 0; i < 4; i++)
    if (adj[ind] < adj[i]) ind = i;
  return angles[ind];
  
}

precision vector::maxAngle(precision a, precision b, precision c, precision d)
{
  int ind = 0;
  precision angles[] = {a,b,c,d};
  precision adj[] = {a,b,c,d};
  for (int i = 0; i < 4; i++) //Correct negative underflow angles, and positive overflow angles
    adj[i] = angles[i] < -180 ? angles[i] + 360 : (angles[i] > 180 ? angles[i] - 360 : angles[i]);
  for (int i = 0; i < 4; i++)
    if (adj[ind] > adj[i]) ind = i;
  return angles[ind];
}
precision vector::angleToViewportLerp(precision angle, precision fovX)
{
  precision t = 0.5;
  /*takes an angle, corrects it, and returns a t
   0* is straight ahead.
   0* -> 0.5
   fov/2 -> 0
   -fov/2 -> 1
   350 -> -10 -> [0,1]
   */
  angle = angle < -180 ? angle + 360 : (angle > 180 ? angle - 360 : angle);

  return map(angle, fovX/2.0, -fovX/2.0, 0, 1);
}

precision vector::distance(point a, point b) { 
    return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2) );
  }
  precision vector::distance(point p) { 
    return sqrt( pow(p.x-x, 2) + pow(p.y-y, 2) + pow(p.z-z, 2) );
  }
  precision vector::pivotAngle(point a, point b) {
    precision theta = 0;
    precision top = a.x*b.x + a.y*b.y+a.z*b.z;
    precision bottom = a.distance({0,0,0}) * b.distance({0,0,0});
    //R2D::Text(("Bottom:" + std::to_string(bottom)+"\n").data());
    theta = top/bottom;
    if(theta >= 1 || theta <= -1)
    std::__throw_logic_error("Invalid Theta");
    //R2D::Text(("Theta:" + std::to_string(theta)+"\n").data());
    return acos(theta);
  }

  precision vector::pivotAngleSigned(point a, point b) {
    return angleTo(a) - angleTo(b);
  }
  precision vector::horizontalDistance(point p)
  {
    return sqrt( pow(p.x-x, 2) + pow(p.y-y, 2));
  }

  precision vector::pitchTo(point p, point orientation, precision angle)
  {
    //We know that a negative z means negative angle, and vice-versa
    precision dz = p.z - z;
    precision dl = distance(p);// * cos(angle * PI/180.0);
    //R2D::Text(("ASIN: " + std::to_string(asin(dz/dl)) + "\n").data());
    //R2D::Text(("\tfrc: " + std::to_string(dz/dl) + "\n").data());
    //R2D::Text(("\tdz: " + std::to_string(dz) + "\n").data());
    //R2D::Text(("\tdl: " + std::to_string(dl) + "\n").data());
    precision theta = abs(asin(dz/dl) * 180.0/PI);
    return dz < 0 ? -theta : theta;
  }

  precision vector::angleTo(point p)
  {
    precision dx = p.x - x, dy = p.y - y;
    if (abs(dx) < 0.01 && abs(dy) < 0.01) return 0;
    if (abs(dx) < 0.01) return dy > 0 ? 90 : 270;
    if (abs(dy) < 0.01) return dx > 0 ? 0 : 180;
    precision tan = atan(dy/abs(dx));
    precision ang = abs(map(tan, -PI, PI, -90, 90));
    if (dx > 0 && dy >= 0) ang = atan(dy/dx) * 180.0/PI;
    if (dx < 0 && dy >= 0) ang = (180.0 - 2.0*ang);
    if (dy < 0) ang = ang + ang;
    if (dy < 0 && dx <= 0) ang = ang +180;
    if (dy < 0 && dx > 0) ang = 360 - ang;
    return ang;
  }
  precision vector::signedAngleTo(point p)
  {
    precision dx = p.x - x, dy = p.y - y;
    if (abs(dx) < 0.01 && abs(dy) < 0.01) return 0;
    if (abs(dx) < 0.01) return dy > 0 ? 90 : -90;
    if (abs(dy) < 0.01) return dx > 0 ? 0 : 180;
    precision tan = atan(dy/abs(dx));
    precision ang = abs(map(tan, -PI, PI, -90, 90));
    if (dx > 0 && dy >= 0) ang = atan(dy/dx) * 180.0/PI;
    if (dx < 0 && dy >= 0) ang = (180.0 - 2.0*ang);
    if (dy < 0) ang = ang + ang;
    if (dy < 0 && dx <= 0) ang = ang +180;
    if (dy < 0 && dx > 0) ang = 360 - ang;
    return ang > 180 ? -360+ang : ang;
  }
  point vector::normalize() { 
    point me = *this;
    precision scal = distance(me); 
    x = x/scal; 
    y = y/scal; 
    z = z/scal; 
    return me;
  }
  point* vector::lerp(point a, point b, precision t) { 
    return new point( map(t, 0, 1, a.x, b.x), map(t, 0, 1, a.y, b.y), map(t, 0, 1, a.z, b.z) );
  }
  point* vector::lerp(point b, precision t) { 
    return new point( map(t, 0, 1, x, b.x), map(t, 0, 1, y, b.y), map(t, 0, 1, z, b.z) );
  }
  point* vector::fwd(precision angle, precision pitch) { 
    return new point(x + cos(angle*PI/180.0), y + sin(angle*PI/180.0), z + sin(pitch*PI/180.0));
  }
  bool vector::isPointInViewport(vector camera, vector orientation, precision fovX) { 
    return (abs(camera.pivotAngle( *camera.fwd(orientation.x, orientation.y), *this ) * 180.0/PI) < fovX/2);
  }