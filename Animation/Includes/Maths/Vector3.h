#pragma once
#include <string>

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

        // -- Operators -- //
        template <typename T> bool    operator==(const T& val) const;
        template <typename T> bool    operator!=(const T& val) const;
        template <typename T> Vector3 operator+ (const T& val) const;
                              Vector3 operator- (            ) const;
        template <typename T> Vector3 operator- (const T& val) const;
        template <typename T> Vector3 operator* (const T& val) const;
        template <typename T> Vector3 operator/ (const T& val) const;
        template <typename T> void    operator+=(const T& val);
        template <typename T> void    operator-=(const T& val);
        template <typename T> void    operator*=(const T& val);
        template <typename T> void    operator/=(const T& val);
                              float   Dot       (const Vector3& v) const;
                              Vector3 Cross     (const Vector3& v) const;

        // -- Methods -- //

        // Length.
        float GetLength() const;              // Returns the vector's length.
        void  SetLength(const float& length); // Modifies the vector's length to correspond to the given value.

        // Normalization.
        void    Normalize();           // Normalizes the given vector so that its length is 1.
        Vector3 GetNormalized() const; // Returns a normalized copy of the vector.

        // Negation.
        void    Negate();           // Negates the vector's coordinates.
        Vector3 GetNegated() const; // Returns a negated copy of the vector.

        // Copy signs.
        void    CopySign     (const Vector3& source);       // Copies the signs from the source vector to this vector.
        Vector3 GetCopiedSign(const Vector3& source) const; // Returns a copy of this vector with the given vector's signs.

        // Interprets the vector as a point and returns the distance to another point.
        float GetDistanceFromPoint(const Vector3& p) const;

        // Angles.
        float GetXAngle() const; // Returns the pitch angle (in radians) of the given vector.
        float GetYAngle() const; // Returns the yaw angle (in radians) of the given vector.
        float GetXAngleWithVector3(const Vector3& v) const; // Returns the angle (in radians) between two vectors.
        float GetYAngleWithVector3(const Vector3& v) const; // Returns the angle (in radians) between two vectors.

        // Rotation.
        void    Rotate    (const Vector3& angles);       // Rotates the vector by the given angle.
        Vector3 GetRotated(const Vector3& angles) const; // Returns a copy of the vector rotated by the given angle.
        
        // Linearly interpolates from start to dest.
        static Vector3 Lerp(const Vector3& start, const Vector3& dest, const float& val);

        // Conversions.
        Vector4     ToVector4() const;                        // Creates a Vector4 from this vector.
        std::string ToString(const int& precision = 2) const; // Returns the vector's contents as a string.
    };


    // Returns the coordinates of a point on a sphere of radius r, using the given angles.
    Vector3 GetSphericalCoords(const float& r, const float& pitch, const float& yaw);
}

#include "Vector3.inl"
