#include "Maths.h"
#include <cmath>
using namespace Maths;


// Constructors.
Vector2::Vector2() : x(0), y(0) {}; // Null vector.
Vector2::Vector2(const float& _x, const float& _y) : x(_x), y(_y) {}; // Vector with 2 coordinates.
Vector2::Vector2(const Vector2& p1, const Vector2& p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}; // Vector from 2 points.
Vector2::Vector2(const float& rad, const float& length, const bool& isAngle) : x(cos(rad)* length), y(sin(rad)* length) {}; // Vector from angle (useless bool).

// ---------- VECTOR2 OPERATORS ---------- //

// Copy constructor.
void Vector2::operator=(const Vector2& other) { x = other.x; y = other.y; }

// Vector2 dot product.
float Vector2::operator&(const Vector2& val) const { return (x * val.x) + (y * val.y); }

// Vector2 cross product.
float Vector2::operator^(const Vector2& val) const { return (x * val.y) - (y * val.x); }

// Vector2 negation.
Vector2 Vector2::operator-()                 const { return { -x, -y }; }

// ------------ VECTOR2 METHODS ----------- //

// Returns the middle of the given vector.
Vector2 Vector2::getMiddle()                          const { return Vector2(x / 2, y / 2); }

// Returns the length of the given vector.
float Vector2::getLength()                            const { return sqrt(sqpow(x) + sqpow(y)); }

// Modifies the length of the given vector to correspond to the given value.
void Vector2::setLength(const float& length) { *(this) = Vector2(getAngle(), length, true); }

// Normalizes the given vector so that its length is 1.
void Vector2::normalize() { x /= getLength(); y /= getLength(); }

// Normalizes the given vector so that its length is 1.
Vector2 Vector2::getNormalized()                      const { return Vector2(x / getLength(), y / getLength()); }

// Negates both of the coordinates of the given vector.
void Vector2::negate() { *(this) = Vector2(-x, -y); }

// Copies the signs from the source vector to the destination vector.
void Vector2::copysign(const Vector2& source) { *(this) = Vector2(std::copysign(x, source.x), std::copysign(y, source.y)); }

// Copies the signs from the source vector to the destination vector.
Vector2 Vector2::getCopiedSign(const Vector2& source) const { return Vector2(std::copysign(x, source.x), std::copysign(y, source.y)); }

// Returns the normal of a given vector.
Vector2 Vector2::getNormal()                          const { return Vector2(-y, x); }

// Interprets the vector as a point and returns the distance to another point.
float Vector2::getDistanceFromPoint(const Vector2& p) const { return Vector2(*this, p).getLength(); }

// Returns the angle (in radians) of the given vector.
float Vector2::getAngle()                             const { return std::copysign(std::acos(getNormalized().x), std::asin(getNormalized().y)); }

// Returns the angle (in radians) between two vectors.
float Vector2::getAngleWithVector2(const Vector2& v)  const
{
    float this_angle = getAngle();
    float v_angle = v.getAngle();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

// Rotates the given vector by the given angle.
void Vector2::rotate(const float& angle)
{
    float this_length = getLength();
    float this_angle = getAngle();
    *(this) = Vector2(this_angle + angle, this_length, true);
}

// Rotates the point around the given pivot point by the given angle (in rad).
void Vector2::rotateAsPoint(const Vector2& pivot, const float& angle)
{
    float s = sin(angle);
    float c = cos(angle);

    // Translate the point back to the origin.
    x -= pivot.x;
    y -= pivot.y;

    // Rotate the point around the origin.
    float xnew = x * c - y * s;
    float ynew = x * s + y * c;

    // Translate point back to the pivot.
    x = xnew + pivot.x;
    y = ynew + pivot.y;
}




// Calculates linear interpolation for a value from a start point to an end point.
Vector2 Maths::point2Lerp(const float& val, const Vector2& start, const Vector2& end)
{
    return Vector2(lerp(val, start.x, end.x),
        lerp(val, start.y, end.y));
}
