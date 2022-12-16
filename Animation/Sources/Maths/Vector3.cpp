#include "Maths/Maths.h"
#include <cmath>
using namespace Maths;


// Constructors.
Vector3::Vector3()                                                  : x(0),   y(0),   z(0)                           {}; // Null vector.
Vector3::Vector3(const float& all)                                  : x(all), y(all), z(all)                         {}; // Vector with equal coordinates.
Vector3::Vector3(const float& _x, const float& _y, const float& _z) : x(_x),  y(_y),  z(_z)                          {}; // Vector with 3 coordinates.
Vector3::Vector3(const Vector3& p1, const Vector3& p2)              : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}; // Vector from 2 points.
Vector3::Vector3(const Vector3& angles, const float& length)        : x(0),   y(0),   z(0)
{
    *this = (Vector4(0, 0, 1, 1) * Mat4::FromEuler(-angles)).ToVector3(true) * length;
}

// ---------- VECTOR3 OPERATORS ---------- //

// Vector3 negation.
Vector3 Vector3::operator-() const { return { -x, -y, -z }; }

// Vector3 dot product.
float Vector3::Dot(const Vector3& v) const { return (x * v.x) + (y * v.y) + (z * v.z); }

// Vector3 cross product.
Vector3 Vector3::Cross(const Vector3& v) const { return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x)); }

// ------------ VECTOR3 METHODS ----------- //

// Length.
float Vector3::GetLength() const { return sqrt(sqpow(x) + sqpow(y) + sqpow(z)); }
void  Vector3::SetLength(const float& length) { Normalize(); *this *= length; }

// Normalization.
void Vector3::Normalize()
{
    if (x == 0 && y == 0 && z == 0) return;
    
    const float length = GetLength();
    x /= length;
    y /= length;
    z /= length;
}
Vector3 Vector3::GetNormalized() const
{
    if (x == 0 && y == 0 && z == 0) return Vector3();
    
    const float length = GetLength();
    return Vector3(x / length, y / length, z / length);
}

// Negation.
void    Vector3::Negate    ()       { x *= -1; y *= -1; z *= -1; }
Vector3 Vector3::GetNegated() const { return Vector3(x*-1, y*-1, z*-1); }

// Copy signs.
void    Vector3::CopySign     (const Vector3& source)       { *this = GetCopiedSign(source); }
Vector3 Vector3::GetCopiedSign(const Vector3& source) const { return Vector3(std::copysign(x, source.x), std::copysign(y, source.y), std::copysign(z, source.z)); }

// Interprets the vector as a point and returns the distance to another point.
float Vector3::GetDistanceFromPoint(const Vector3& p) const { return Vector3(*this, p).GetLength(); }

// Angles.
float Vector3::GetXAngle() const { return asin(-y); }
float Vector3::GetYAngle() const { return atan2(x, z); }
float Vector3::GetXAngleWithVector3(const Vector3& v) const
{
    const float thisAngle  = GetXAngle();
    const float otherAngle = v.GetXAngle();
    return (thisAngle >= otherAngle ? (thisAngle - otherAngle) : (otherAngle - thisAngle));
}
float Vector3::GetYAngleWithVector3(const Vector3& v) const
{
    const float thisAngle  = GetYAngle();
    const float otherAngle = v.GetYAngle();
    return (thisAngle >= otherAngle ? (thisAngle - otherAngle) : (otherAngle - thisAngle));
}

// Rotation.
void Vector3::Rotate(const Vector3& angles) 
{ 
    *this = GetRotated(angles);
}
Vector3 Vector3::GetRotated(const Vector3& angles) const
{
    return Vector3(Vector3(GetXAngle() + angles.x, GetYAngle() + angles.y, angles.z), GetLength());
}

// Interpolation.
Vector3 Vector3::Lerp(const Vector3& start, const Vector3& dest, const float& val)
{
    return Vector3(lerp(start.x, dest.x, val),
                   lerp(start.y, dest.y, val),
                   lerp(start.z, dest.z, val));
}

// Creates a Vector4 from this vector.
Vector4 Vector3::ToVector4() const { return Vector4(x, y, z, 1); }

// Returns the vector's contents as a string.
std::string Vector3::ToString(const int& precision) const
{
    std::ostringstream string;
    string.precision(precision);
    string << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z;
    return string.str();
}


// Returns the coordinates of a point on a sphere of radius r, using the given angles.
Vector3 Maths::GetSphericalCoords(const float& r, const float& pitch, const float& yaw)
{
    return { r * sinf(pitch) * cosf(yaw),
                   r * sinf(pitch) * sinf(yaw),
                   r * cosf(pitch) };
}
