#pragma once

namespace Maths
{
    class Vector3;

    // Point in 3D space with homogeneous coordinates.
    // TODO: Remove most computations from this class and leave them to Vector3.
    class Vector4
    {
    public:
        // Attributes.
        float x, y, z, w;

        // -- Constructors & Destructor -- //
        Vector4();                                                                   // Null vector.
        Vector4(const float& _x, const float& _y, const float& _z, const float& _w); // Vector with 3 coordinates.
        Vector4(const Vector3& vec, const float& _w);                                // Vector4 from vector3.
        Vector4(const Vector4& p1, const Vector4& p2, const float& _w);              // Vector4 from 2 points.
        Vector4(const Vector3& angles, const float& length, const float& _w);        // Vector4 from angles.

        // -- Operators -- //
        template <typename T> bool    operator==(const T& val) const;
        template <typename T> bool    operator!=(const T& val) const;
        template <typename T> Vector4 operator+ (const T& val) const;
                              Vector4 operator- (            ) const;
        template <typename T> Vector4 operator- (const T& val) const;
        template <typename T> Vector4 operator* (const T& val) const;
        template <typename T> Vector4 operator/ (const T& val) const;
        template <typename T> void    operator+=(const T& val);
        template <typename T> void    operator-=(const T& val);
        template <typename T> void    operator*=(const T& val);
        template <typename T> void    operator/=(const T& val);
                              float   Dot       (const Vector4& v) const;
                              Vector3 Cross     (const Vector4& v) const;

        // -- Methods -- //

        // Homogenization.
        void    Homogenize();           // Homogenizes the vector by dividing its elements by w.
        Vector4 GetHomogenized() const; // Returns a homogenized copy of the vector.

        // Length.
        float GetLength() const;              // Returns the length of the vector.
        void  SetLength(const float& length); // Modifies the vector's length to correspond to the given value.

        // Normalization.
        void    Normalize();           // Normalizes the vector so that its length is 1.
        Vector4 GetNormalized() const; // Returns a normalized copy of the vector.

        // Negation.
        void    Negate();           // Negates the vector's coordinates.
        Vector4 GetNegated() const; // Returns a negated copy of the vector.

        // Copy signs.
        void    CopySign     (const Vector4& source);       // Copies the signs from the source vector to this vector.
        Vector4 GetCopiedSign(const Vector4& source) const; // Returns a copy of this vector with the given vector's signs.

        // Interprets the vector as a point and returns the distance to another point.
        float GetDistanceFromPoint(const Vector4& p) const;

        // Angles.
        float GetXAngle() const; // Returns the pitch angle (in radians) of the given vector.
        float GetYAngle() const; // Returns the yaw angle (in radians) of the given vector.
        float GetXAngleWithVector4(const Vector4& v) const; // Returns the angle (in radians) between two vectors.
        float GetYAngleWithVector4(const Vector4& v) const; // Returns the angle (in radians) between two vectors.

        // Rotation.
        void    Rotate    (const Vector3& angles);       // Rotates the vector by the given angle.
        Vector4 GetRotated(const Vector3& angles) const; // Returns a copy of the vector rotated by the given angle.

        // Conversions.
        Vector3     ToVector3(const bool& homogenizeVec = false) const; // Creates a Vector3 from this vector.
        std::string ToString (const int&  precision = 2)         const; // Returns the vector's contents as a string.
    };
}

#include "Vector4.inl"
