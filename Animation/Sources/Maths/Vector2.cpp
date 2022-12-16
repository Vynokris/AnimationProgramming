#include "Maths/Maths.h"
#include <cmath>
using namespace Maths;


// Constructors.
Vector2::Vector2() : x(0), y(0) {}; // Null vector.
Vector2::Vector2(const float& _x, const float& _y) : x(_x), y(_y) {}; // Vector with 2 coordinates.
Vector2::Vector2(const Vector2& p1, const Vector2& p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}; // Vector from 2 points.
Vector2::Vector2(const float& rad, const float& length, const bool& isAngle) : x(cos(rad)* length), y(sin(rad)* length) {}; // Vector from angle (useless bool).

// ---------- VECTOR2 OPERATORS ---------- //

// Vector2 negation.
Vector2 Vector2::operator-() const { return { -x, -y }; }

// Vector2 dot product.
float Vector2::Dot(const Vector2& v) const { return (x * v.x) + (y * v.y); }

// Vector2 cross product.
float Vector2::Cross(const Vector2& v) const { return (x * v.y) - (y * v.x); }

// ------------ VECTOR2 METHODS ----------- //

// Length.
float Vector2::GetLength()              const { return sqrt(sqpow(x) + sqpow(y)); }
void  Vector2::SetLength(const float& length) { Normalize(); *this *= length; }

// Normalization.
void    Vector2::Normalize    ()       { x /= GetLength(); y /= GetLength(); }
Vector2 Vector2::GetNormalized() const { return Vector2(x / GetLength(), y / GetLength()); }

// Negation
void    Vector2::Negate    ()       { x *= -1; y *= -1; }
Vector2 Vector2::GetNegated() const { return Vector2(-x, -y); }

// Copy signs.
void    Vector2::CopySign     (const Vector2& source)       { *(this) = GetCopiedSign(source); }
Vector2 Vector2::GetCopiedSign(const Vector2& source) const { return Vector2(std::copysign(x, source.x), std::copysign(y, source.y)); }

// Returns the normal of a given vector.
Vector2 Vector2::GetNormal() const { return Vector2(-y, x); }

// Interprets the vector as a point and returns the distance to another point.
float Vector2::GetDistanceFromPoint(const Vector2& p) const { return Vector2(*this, p).GetLength(); }

// Angle.
float Vector2::GetAngle() const { return std::copysign(std::acos(GetNormalized().x), std::asin(GetNormalized().y)); }
float Vector2::GetAngleWithVector2(const Vector2& v)  const
{
    const float thisAngle  = GetAngle();
    const float otherAngle = v.GetAngle();
    return (thisAngle >= otherAngle ? (thisAngle - otherAngle) : (otherAngle - thisAngle));
}

// Rotation.
void Vector2::Rotate(const float& angle)
{
    const float length = GetLength();
    const float origAngle = GetAngle();
    *this = Vector2(origAngle + angle, length, true);
}
void Vector2::RotateAsPoint(const Vector2& pivot, const float& angle)
{
    const float s = sin(angle);
    const float c = cos(angle);

    // Translate the point back to the origin.
    x -= pivot.x;
    y -= pivot.y;

    // Rotate the point around the origin.
    const float xNew = x * c - y * s;
    const float yNew = x * s + y * c;

    // Translate point back to the pivot.
    x = xNew + pivot.x;
    y = yNew + pivot.y;
}

// Calculates linear interpolation for a value from a start point to an end point.
Vector2 Vector2::Lerp(const Vector2& start, const Vector2& dest, const float& val)
{
    return Vector2(lerp(start.x, dest.x, val),
                   lerp(start.y, dest.y, val));
}


// Returns the vector's contents as a string.
std::string Vector2::ToString(const int& precision) const
{
    std::ostringstream string;
    string.precision(precision);
    string << std::fixed << x << ", " << std::fixed << y;
    return string.str();
}
