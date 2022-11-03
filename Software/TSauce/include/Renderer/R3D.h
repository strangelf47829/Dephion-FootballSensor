#include "GLDriver.h"
#include "vectormath.h"
#include "Poly.h"
#include "Object.h"

#ifndef R3D_H_
#define R3D_H_

class R3D
{
    private:
        const int occlusionLeniency = 7;
        float cullNear = 0;
        float cullFar = 5000000;
        void calculateCulledPoly();
        
    public:
        void Render(obj* object, int skip);
        void cull(obj* object, int skip);
        void Render(Poly p);
        float fovX, fovY;
        vector Camera;
        vector orientation;
        

};

#endif