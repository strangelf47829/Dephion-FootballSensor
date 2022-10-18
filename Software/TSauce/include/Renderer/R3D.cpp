#include "R3D.h"
#include "vectormath.h"
#include "R2D.h"
#include "Poly.h"
#include "Object.h"

#define yaw orientation.y
#define pitch orientation.x

#define WIREMESH true

point R3D::Camera(0,0,0);
point R3D::orientation(0,0,0);

float R3D::fovX = 90;
float R3D::fovY = 50;


void R3D::Render(obj* object)
{
    cull(object);
}

void R3D::cull(obj* object)
{
    float mnYaw = -fovX/2, mxYaw = fovX/2;

    //First, cull on visibility
    int polyN = 0;

    


    while(polyN < object->polyCount)
    {
        Poly* polyPtr = *(object->poly+polyN*sizeof(Poly*));
        if(polyPtr->a.isPointInViewport(Camera, orientation) || polyPtr->b.isPointInViewport(Camera, orientation) || polyPtr->c.isPointInViewport(Camera, orientation))
        {
            Render(*polyPtr);
        }
        polyN++;
    }

}

void R3D::Render(Poly p)
{
    Poly* polyPtr = &p;
    float dA = Camera.distance(polyPtr->a), dB = Camera.distance(polyPtr->b), dC = Camera.distance(polyPtr->c), dM = Camera.distance(polyPtr->midpoint);
    float nA = Camera.angleTo(polyPtr->a) - yaw, nB = Camera.angleTo(polyPtr->b) - yaw, nC = Camera.angleTo(polyPtr->c) - yaw, nM = Camera.angleTo(polyPtr->midpoint) - yaw;
    float pA = Camera.pitchTo(polyPtr->a, orientation, nA) - pitch, pB = Camera.pitchTo(polyPtr->b, orientation, nB) - pitch, pC = Camera.pitchTo(polyPtr->c, orientation, nC) - pitch, pM = Camera.pitchTo(polyPtr->midpoint, orientation, nM);
    float minYaw = vector::minAngle(nA, nB, nC, -40), maxYaw = vector::maxAngle(nA, nB, nC, 40);
    float minPitch = __max(__min(pA, __min(pB, pC)), -fovY/2), maxPitch = __min(__max(pA, __max(pB, pC)), fovY/2);
    float minDist = __min(dA, __min(dB, dC));

    //Depth mask

    

    float nS = 0;
    float pS = 0;
    if (nA != nB && nB != nC && nA != nC) { nS = (nA != minYaw && nA != maxYaw) ? nA : ((nB != minYaw && nB != maxYaw) ? nB : nC); pS = nS == nA ? pA : (nS == nB ? pB : pC); }
    else if(nA == nB) { nS = pA > pB ? nA-0 : nB-0; pS = pA > pB ? pA : pB; }
    else if(nB == nC) { nS = pB > pC ? nB-0 : nC-0; pS = pB > pC ? pB : pC; }
    else { nS = pA > pC ? nA : nC; pS = pA > pC ? pA : pC; }

    if(WIREMESH)
    {
        R2D::DrawHV(nA, pA, nB, pB);
        //R2D::DrawHV(nA, pA, nC, pC);
        R2D::DrawHV(nC, pC, nB, pB);
    }
    int mindexH = vector::angleToIndex(minYaw), maxdexH = vector::angleToIndex(maxYaw), middexH = vector::angleToIndex(nS);
    int mindexV = vector::pitchToIndex( minYaw == nA ? pA : (minYaw == nB ? pB : pC)), maxdexV = vector::pitchToIndex(maxYaw == nA ? pA : (maxYaw == nB ? pB : pC)), middexV = vector::pitchToIndex(pS);
        
}

void R3D::calculateCulledPoly()
{
    //TODO: DepthMask
    int ind = 0;

}