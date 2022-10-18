#include "GLDriver.h"
#include "vectormath.h"
#include "Poly.h"
#include "Object.h"

#ifndef R3D_H_
#define R3D_H_

#define xRes Driver::SCREEN_WIDTH
#define yRes Driver::SCREEN_HEIGHT

class R3D
{
    private:
        

        //x: pitch, y: yaw, z: roll
        
        
        static const int occlusionLeniency = 7;

        static constexpr float cullNear = 0;
        static constexpr float cullFar = 500;

        //CulledPolly


        //objects
        static void calculateCulledPoly();

        


    public:
        static void Render(obj* object);
        static void cull(obj* object);
        static void Render(Poly p);
        static float fovX, fovY;
        static vector Camera;
        static vector orientation;

};

#endif