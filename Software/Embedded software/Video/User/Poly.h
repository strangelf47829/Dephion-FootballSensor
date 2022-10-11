/*
 * Poly.h
 *
 *  Created on: Oct 11, 2022
 *      Author: stran
 */

#ifndef POLY_H_
#define POLY_H_

class Poly {
public:



	Poly();
	virtual ~Poly();
	Poly& operator=(Poly &&other);
	Poly& operator=(const Poly &other);
	Poly(Poly &&other);
	Poly(const Poly &other);
};

#endif /* POLY_H_ */
