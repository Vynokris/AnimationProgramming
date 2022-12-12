#pragma once

namespace Maths
{
    class Vector4;

    // Vector class that holds values for x, y and z (3 dimensions).
    class Vector3
    {
    public:
        // -- Attributes -- //
        float x, y, z;

        // -- Constructors & Destructor -- //
        Vector3();                                                  // Null vector.
        Vector3(const float& all);                                  // Vector with equal coordinates.
        Vector3(const float& _x, const float& _y, const float& _z); // Vector with 3 coordinates.
        Vector3(const Vector3& p1, const Vector3& p2);              // Vector from 2 points.
        Vector3(const Vector3& angles, const float& length);        // Vector from angles (useless bool).
        ~Vector3() {}

        // -- Operators -- //
                              void    operator= (const Vector3& other);
        template <typename T> bool    operator==(const T& val) const;
        template <typename T> bool    operator!=(const T& val) const;
        template <typename T> Vector3 operator+ (const T& val) const;
        template <typename T> Vector3 operator- (const T& val) const;
        template <typename T> Vector3 operator* (const T& val) const;
        template <typename T> Vector3 operator/ (const T& val) const;
        template <typename T> void    operator+=(const T& val);
        template <typename T> void    operator-=(const T& val);
        template <typename T> void    operator*=(const T& val);
        template <typename T> void    operator/=(const T& val);
                              float   operator& (const Vector3& val) const;
                              Vector3 operator^ (const Vector3& val) const;
                              Vector3 operator- ()                   const;

        // -- Methods -- //

        // Returns the length of the given vector.
        float getLength() const;
        // Modifies the length of the given vector to correspond to the given value.
        void setLength(const float& length);

        // Normalizes the given vector so that its length is 1.
        void normalize();
        Vector3 getNormalized() const;

        // Negates both of the coordinates of the given vector.
        void negate();
        Vector3 getNegated() const;

        // Copies the signs from the source vector to the destination vector.
        void copysign(const Vector3& source);
        Vector3 getCopiedSign(const Vector3& source) const;

        // Interprets the vector as a point and returns the distance to another point.
        float getDistanceFromPoint(const Vector3& p) const;

        // Returns the angle (in radians) of the given vector.
        float getXAngle() const;
        float getYAngle() const;

        // Returns the angle (in radians) between two vectors.
        float getXAngleWithVector3(const Vector3& v) const;
        float getYAngleWithVector3(const Vector3& v) const;

        // Rotates the given vector by the given angle.
        void rotate(const Vector3& angles);
        Vector3 getRotated(const Vector3& angles) const;

        // Creates a Vector4 from this vector.
        Vector4 toVector4() const;
    };

    // Calculates linear interpolation for a value from a start point to an end point.
    Vector3 point3Lerp(const float& val, const Vector3& start, const Vector3& end);

    // Returns the coordinates of a point on a sphere of radius r, using the given angles.
    Vector3 getSphericalCoords(const float& r, const float& pitch, const float& yaw);
}

#include "Vector3.inl"
