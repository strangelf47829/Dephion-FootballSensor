/*
 * object.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */

#ifndef VMATH_H_
#define VMATH_H_

class vector {
	public:
		double x;
        double y;
        double z;
};

class line {
	public:
		vector a;
        vector b;
        vector getMidPoint();
};

#endif /* VMATH_H_ */