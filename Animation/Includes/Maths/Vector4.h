#pragma once
#include "Matrix.h"

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
        Vector4(const float& _x, const float& _y, const float& _z, const float& _w); // Vector with 4 coordinates.
        Vector4(const Vector3& vec, const float& _w);                                // Vector4 from Vector3.

        // -- Operators -- //
        template <typename T> bool    operator==(const T& val) const;
        template <typename T> bool    operator!=(const T& val) const;
        Vector4 operator*(const Mat4& val) const;

        // -- Methods -- //

        // Homogenization.
        void    Homogenize();           // Homogenizes the vector by dividing its elements by w.
        Vector4 GetHomogenized() const; // Returns a homogenized copy of the vector.

        // Conversions.
        Vector3     ToVector3(const bool& homogenizeVec = false) const; // Creates a Vector3 from this vector.
        std::string ToString (const int&  precision = 2)         const; // Returns the vector's contents as a string.
    };
}

#include "Vector4.inl"
