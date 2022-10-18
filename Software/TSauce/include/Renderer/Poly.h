#include "vectormath.h"
/*
 * Poly.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */

#ifndef POLY_H_
#define POLY_H_

class Poly {
public:

	Poly();
	Poly(point a, point b, point c);
	point midpoint;
	
	point a;
	point b;
	point c;

	point RefreshMidpoint();
};

#endif /* POLY_H_ */
