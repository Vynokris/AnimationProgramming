#include "Maths/Maths.h"
using namespace Maths;


// Constructors.
Vector4::Vector4()                                                                   : x(0),  y(0),  z(0),  w(1)  {};                            // Null vector.
Vector4::Vector4(const float& _x, const float& _y, const float& _z, const float& _w) : x(_x), y(_y), z(_z), w(_w) {};                            // Vector with 4 coordinates.
Vector4::Vector4(const Vector3& vec, const float& _w)                                : x(vec.x), y(vec.y), z(vec.z), w(_w) {};                   // Vector from Vector3.

// Homogenization.
void    Vector4::Homogenize()           { x /= w; y /= w; z /= w; w = 1; }
Vector4 Vector4::GetHomogenized() const { return Vector4(x/w, y/w, z/w, 1); }

// Creates a Vector3 from this vector.
Vector3 Vector4::ToVector3(const bool& homogenizeVec) const
{
    if (homogenizeVec)
        return Vector3(x / w, y / w, z / w);
    return Vector3(x, y, z);
}

// Returns the vector's contents as a string.
std::string Vector4::ToString(const int& precision) const
{
    std::ostringstream string;
    string.precision(precision);
    string << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z << ", " << std::fixed << w;
    return string.str();
}
