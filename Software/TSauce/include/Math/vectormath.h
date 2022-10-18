/*
 * vectormath.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */
#ifndef VMATH_H_
#define VMATH_H_

typedef long double dimension;
typedef double precision;

class vector {
	public:
	/// @brief The x value of the vector
	dimension x = 0;

        /// @brief The y value of the vector
        dimension y = 0;
        
        /// @brief The z value of the vector
        dimension z = 0;

        /// @brief Returns the distance between 2 vectors
        /// @param a The first vector
        /// @param b The second vector
        /// @return the distance between "a" and "b"
        static precision distance(vector a, vector b);
        
        /// @brief Calculates the distance between this point and "p"
        /// @param p The vector to get the distance to
        /// @return The distance between this point and "p"
        precision distance(vector p);

        /// @brief Given a vector "pivot", calculate the angles between "pivot" and "a", and "pivot" and "b". Then, return the difference.
        /// @param a The reference Vector
        /// @param b The vector to perform the calculation on 
        /// @param pivot The vector to pivot "a" and "b" around
        /// @return the degrees, in radians, between "a" and "b" pivoted around "pivot"
        static precision pivotAngle(vector a, vector b, vector pivot);

        /// @brief See vector::pivotAngle.
        /// @return the signed angle, with "a" taken as the reference
        static precision pivotAngleSigned(vector a, vector b, vector pivot);

        /// @brief Given a vector, calculate the angles between the vector and "a", and the vector and "b". Then, return the difference.
        /// @param a The reference Vector
        /// @param b The vector to perform the calculation on 
        /// @return the degrees, in radians, between "a" and "b" pivoted around this vector
        /// @sa vector::pivotAngle
        precision pivotAngle(vector a, vector b);

        /// @brief See pivotAngle.
        /// @return the signed angle, with "a" taken as the reference
        precision pivotAngleSigned(vector a, vector b);

        /// @brief Returns the distance between vector "a" and vector "b", ignoring the z dimension
        /// @param a The reference vector
        /// @param b The vector to get the distance to
        /// @return The horizontal distance between vector "a" and "b"
        static precision horizontalDistance(vector a, vector b);

        /// @brief Returns the distance between this vector and vector "p", ignoring the z dimension
        /// @param p The vector to get the distance to
        /// @return The horizontal distance between this vector and "p"
        precision horizontalDistance(vector p);

        /// @brief Gets the vertical angle to "p", relative to the horizon of this vector given an orientation and precalculated horizontal angle
        /// @param p The vector to get the vertical angle to
        /// @param angle The precalculated horizontal angle. See "angleTo(vector)"
        /// @return The signed vertical angle
        precision pitchTo(vector p, vector orientation, precision angle);
        
        /// @brief Calculates the angle between the (x,y) of this vector and the (x,y) of "p"
        /// @param p The vector to get the vertical angle to
        /// @return An unsigned horizontal angle
        precision angleTo(vector p);

        /// @brief Calculates the signed angle between the (x,y) of this vector and the (x,y) of "p"
        /// @param p The vector to get the vertical angle to
        /// @return A signed horizontal angle
        precision signedAngleTo(vector p);

        /// @brief scales the (x,y,z) values, so that the length of this vector is 1
        /// @return this 
        vector normalize();

        /// @brief Interpolates between vector "a" and vector and "b"
        /// @param a The vector to interpolate from
        /// @param b The vector to interpolate to
        /// @param t The argument of interpolation
        /// @return a new vector, interpolated between vector "a" and vector and "b".
        static vector* lerp(vector a, vector b, precision t);

        /// @brief Interpolates between this vector and "b"
        /// @param b The vector to interpolate to
        /// @param t The argument of interpolation
        /// @return a new vector, interpolated between this vector and vector "b".
        vector* lerp(vector b, precision t);

        /// @brief returns a new vector, which forms angle "angle" and pitch "pitch" relative to this point
        /// @param angle the angle to add to the point
        /// @param pitch the pitch to add to the point
        /// @return 
        vector* fwd(precision angle, precision pitch);

        /// @brief Is this point within view of the camera?
        /// @param camera The camera vector
        /// @param orientation the orientation of the camera
        /// @return whether the camera can see this point
        bool isPointInViewport(vector camera, vector orientation);

        static precision minAngle(precision a, precision b, precision c, precision d);
        static precision maxAngle(precision a, precision b, precision c, precision d);

        static int angleToIndex(precision angle);
        static int pitchToIndex(precision angle);
        
        vector(dimension a, dimension b, dimension c);
        
        static precision angleToViewportLerp(precision angle);
    
};

typedef vector point;
//class line {
//	public:
//		vector a;
//        vector b;
//        vector getMidPoint();
//};

#endif /* VMATH_H_ */