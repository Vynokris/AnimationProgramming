#include "Maths/Maths.h"
#include <cmath>
using namespace Maths;


// Constructors.
Vector4::Vector4() : x(0), y(0), z(0), w(1) {}; // Null vector.
Vector4::Vector4(const float& _x, const float& _y, const float& _z, const float& _w) : x(_x), y(_y), z(_z), w(_w) {}; // Vector with 3 coordinates.
Vector4::Vector4(const Vector4& p1, const Vector4& p2, const float& _w) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z), w(_w) {}; // Vector from 2 points.
Vector4::Vector4(const Vector3& vec, const float& _w) : x(vec.x), y(vec.y), z(vec.z), w(_w) {}; // Vector from Segment3.
Vector4::Vector4(const float& theta, const float& phi, const float& length, const float& _w, const bool& isAngle) // Vector from angle (useless bool).
{
    x = length * sinf(theta) * cosf(phi);
    y = length * cosf(theta);
    z = length * sinf(theta) * sinf(phi);
    w = _w;
}

// ---------- VECTOR4 OPERATORS ---------- //

// Copy constructor.
void Vector4::operator=(const Vector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }

// Vector4 dot product.
float Vector4::operator&(const Vector4& v)   const { return (x * v.x) + (y * v.y) + (z * v.z); }

// Vector4 cross product.
Vector3 Vector4::operator^(const Vector4& v) const { return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x)); }

// Vector4 negation.
Vector4 Vector4::operator-()                 const { return { -x, -y, -z, w }; }

// ------------ VECTOR4 METHODS ----------- //

// Returns the middle of the given vector.
Vector4 Vector4::getMiddle() const { return Vector4(x / 2, y / 2, z / 2, w); }

// Homogenizes the vector4 by dividing it by w.
void Vector4::homogenize() { *this = Vector4(x / w, y / w, z / w, w / w); }

// Homogenizes the vector4 by dividing it by w.
Vector4 Vector4::getHomogenized() const { return Vector4(x / w, y / w, z / w, w / w); }

// Returns the length of the given vector.
float Vector4::getLength()        const { return sqrt(sqpow(x) + sqpow(y) + sqpow(z)); }

// Modifies the length of the given vector to correspond to the given value.
void Vector4::setLength(const float& length) { *(this) = Vector4(getAngleTheta(), getAnglePhi(), length, true); }

// Normalizes the given vector so that its length is 1.
void Vector4::normalize()
{
    float length = getLength();
    x /= length;
    y /= length;
    z /= length;
}

// Normalizes the given vector so that its length is 1.
Vector4 Vector4::getNormalized() const
{
    float length = getLength();
    return Vector4(x / length, y / length, z / length, w);
}

// Negates both of the coordinates of the given vector.
void Vector4::negate() { *(this) = Vector4(-x, -y, -z, w); }

// Copies the signs from the source vector to the destination vector.
void Vector4::copysign(Vector4 source) { *(this) = Vector4(std::copysign(x, source.x), std::copysign(y, source.y), std::copysign(z, source.z), w); }

// Copies the signs from the source vector to the destination vector.
Vector4 Vector4::getCopiedSign(Vector4 source) const { return Vector4(std::copysign(x, source.x), std::copysign(y, source.y), std::copysign(z, source.z), w); }

// Interprets the vector as a point and returns the distance to another point.
float Vector4::getDistanceFromPoint(const Vector4& p) const { return Vector4(*this, p, w).getLength(); }

// Returns the angle (in radians) of the given vector.
float Vector4::getAngleTheta() const { return acosf(z / getLength()); }

float Vector4::getAnglePhi()   const
{
    if (x > 0) return atanf(y / x);
    if (x < 0) return atanf(y / x) + PI;
    return PI / 2;
}

// Returns the angle (in radians) between two vectors.
float Vector4::getAngleThetaWithVector4(Vector4 v) const
{
    float this_angle = getAngleTheta();
    float v_angle = v.getAngleTheta();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}
float Vector4::getAnglePhiWithVector4(Vector4 v) const
{
    float this_angle = getAnglePhi();
    float v_angle = v.getAnglePhi();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

// Rotates the given vector by the given angle.
void Vector4::rotate(const float& theta, const float& phi) { *(this) = Vector4(getAngleTheta() + theta, getAnglePhi() + phi, getLength(), w, true); }

// Creates a Vector3 from this vector.
Vector3 Vector4::toVector3(bool homogenizeVec) const
{
    if (homogenizeVec)
        return Vector3(x / w, y / w, z / w);
    else
        return Vector3(x, y, z);
}
