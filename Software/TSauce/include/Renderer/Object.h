#include "vectormath.h"
#include "Poly.h"
/*
 * Object.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */

#ifndef OBJ_H_
#define OBJ_H_

#define PolyOf(a, b) *(a->poly+sizeof(Poly*)*b)

class obj {
    public:
    obj(int count);
    ~obj();
    point transform;
    int polyCount;
    Poly** poly;
};

#endif /* POLY_H_ */