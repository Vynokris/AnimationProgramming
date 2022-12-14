#include "Maths/Maths.h"
#include <cmath>
using namespace Maths;


// Constructors.
Vector4::Vector4()                                                                   : x(0),  y(0),  z(0),  w(1)  {};                            // Null vector.
Vector4::Vector4(const float& _x, const float& _y, const float& _z, const float& _w) : x(_x), y(_y), z(_z), w(_w) {};                            // Vector with 4 coordinates.
Vector4::Vector4(const Vector4& p1, const Vector4& p2, const float& _w)              : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z), w(_w) {}; // Vector from 2 points.
Vector4::Vector4(const Vector3& vec, const float& _w)                                : x(vec.x), y(vec.y), z(vec.z), w(_w) {};                   // Vector from Segment3.
Vector4::Vector4(const Vector3& angles, const float& length, const float& _w)        : x(0),  y(0),  z(0),  w(_w)
{
    *this = (Vector4(0, 0, 1, 1) * Mat4::FromEuler(-angles)).GetHomogenized();
}

// ---------- VECTOR4 OPERATORS ---------- //

// Vector4 negation.
Vector4 Vector4::operator-() const { return { -x, -y, -z, w }; }

// Vector4 dot product.
float Vector4::Dot(const Vector4& v) const { return (x * v.x) + (y * v.y) + (z * v.z); }

// Vector4 cross product.
Vector3 Vector4::Cross(const Vector4& v) const { return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x)); }

// ------------ VECTOR4 METHODS ----------- //

// Homogenization.
void    Vector4::Homogenize()           { x /= w; y /= w; z /= w; w = 1; }
Vector4 Vector4::GetHomogenized() const { return Vector4(x/w, y/w, z/w, 1); }

// Length.
float Vector4::GetLength() const              { return sqrt(sqpow(x) + sqpow(y) + sqpow(z)); }
void  Vector4::SetLength(const float& length) { Normalize(); x *= length; y *= length; z *= length; }

// Normalization.
void Vector4::Normalize()
{
    const float length = GetLength();
    x /= length;
    y /= length;
    z /= length;
}
Vector4 Vector4::GetNormalized() const
{
    const float length = GetLength();
    return Vector4(x / length, y / length, z / length, w);
}

// Negation.
void    Vector4::Negate()           { x *= -1; y *= -1; z *= -1; }
Vector4 Vector4::GetNegated() const { return Vector4(-x, -y, -z, w); }

// Copy signs.
void    Vector4::CopySign     (const Vector4& source) { *this = GetCopiedSign(source); }
Vector4 Vector4::GetCopiedSign(const Vector4& source) const { return Vector4(std::copysign(x, source.x), std::copysign(y, source.y), std::copysign(z, source.z), w); }

// Interprets the vector as a point and returns the distance to another point.
float Vector4::GetDistanceFromPoint(const Vector4& p) const { return Vector4(*this, p, w).GetLength(); }

// Angles.
float Vector4::GetXAngle() const { return asin(-y); }
float Vector4::GetYAngle() const { return atan2(x, z); }
float Vector4::GetXAngleWithVector4(const Vector4& v) const
{
    const float thisAngle  = GetXAngle();
    const float otherAngle = v.GetXAngle();
    return (thisAngle >= otherAngle ? (thisAngle - otherAngle) : (otherAngle - thisAngle));
}
float Vector4::GetYAngleWithVector4(const Vector4& v) const
{
    const float thisAngle  = GetYAngle();
    const float otherAngle = v.GetYAngle();
    return (thisAngle >= otherAngle ? (thisAngle - otherAngle) : (otherAngle - thisAngle));
}

// Rotation.
void Vector4::Rotate(const Vector3& angles) 
{ 
    *this = GetRotated(angles);
}
Vector4 Vector4::GetRotated(const Vector3& angles) const
{
    return Vector4(Vector3(GetXAngle() + angles.x, GetYAngle() + angles.y, angles.z), GetLength(), w);
}

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
