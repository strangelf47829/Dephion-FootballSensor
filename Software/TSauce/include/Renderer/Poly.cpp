/*
 * Poly.cpp
 *
 *  Created on: Oct 11, 2022
 *      Author: stran
 */

#include "Poly.h"
#include "vectormath.h"


Poly::Poly() : a(vector(0,0,0)), b(vector(0,0,0)), c(vector(0,0,0)), midpoint(vector(0,0,0))
{
RefreshMidpoint();
}
Poly::Poly(point e, point f, point g) : a(e), b(f), c(g), midpoint(vector(0,0,0))
{
RefreshMidpoint();
}

point Poly::RefreshMidpoint()
{
    dimension ax = (a.x+b.x+c.x)/3;
    dimension ay = (a.y+b.y+c.y)/3;
    dimension az = (a.z+b.z+c.z)/3;
    this->midpoint = vector(ax,ay,az);
}

