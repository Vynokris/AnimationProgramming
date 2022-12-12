#include "Maths/Maths.h"
#include <cmath>
using namespace Maths;


// Constructors.
Vector3::Vector3()                                                  : x(0),   y(0),   z(0)                           {}; // Null vector.
Vector3::Vector3(const float& all)                                  : x(all), y(all), z(all)                         {}; // Vector with equal coordinates.
Vector3::Vector3(const float& _x, const float& _y, const float& _z) : x(_x),  y(_y),  z(_z)                          {}; // Vector with 3 coordinates.
Vector3::Vector3(const Vector3& p1, const Vector3& p2)              : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}; // Vector from 2 points.
Vector3::Vector3(const Vector3& angles, const float& length)
{
    *this = (Vector4(0, 0, 1, 1) * getRotationMatrix({ -angles.x, -angles.y, -angles.z })).toVector3(true) * length;
}

// ---------- VECTOR3 OPERATORS ---------- //

// Copy constructor.
void Vector3::operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; }

// Vector3 dot product.
float Vector3::operator&(const Vector3& v)   const { return (x * v.x) + (y * v.y) + (z * v.z); }

// Vector3 cross product.
Vector3 Vector3::operator^(const Vector3& v) const { return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x)); }

// Vector3 negation.
Vector3 Vector3::operator-()                 const { return { -x, -y, -z }; }

// ------------ VECTOR3 METHODS ----------- //

// Returns the length of the given vector.
float Vector3::getLength() const { return sqrt(sqpow(x) + sqpow(y) + sqpow(z)); }

// Modifies the length of the given vector to correspond to the given value.
void Vector3::setLength(const float& length) { normalize(); (*this) *= length; }

// Normalizes the given vector so that its length is 1.
void Vector3::normalize()
{
    float length = getLength();
    x /= length;
    y /= length;
    z /= length;
}
Vector3 Vector3::getNormalized() const
{
    if (x == 0 && y == 0 && z == 0)
        return Vector3();
    float length = getLength();
    return Vector3(x / length, y / length, z / length);
}

// Negates both of the coordinates of the given vector.
void    Vector3::negate    ()       { *(this) = getNegated(); }
Vector3 Vector3::getNegated() const { return Vector3(-x, -y, -z); }

// Copies the signs from the source vector to the destination vector.
void    Vector3::copysign     (const Vector3& source)       { *(this) = getCopiedSign(source); }
Vector3 Vector3::getCopiedSign(const Vector3& source) const { return Vector3(std::copysign(x, source.x), std::copysign(y, source.y), std::copysign(z, source.z)); }

// Interprets the vector as a point and returns the distance to another point.
float Vector3::getDistanceFromPoint(const Vector3& p) const { return Vector3(*this, p).getLength(); }

// Returns the angle (in radians) of the given vector.
float Vector3::getXAngle() const { return asin(-y); }
float Vector3::getYAngle() const { return atan2(x, z); }

// Returns the angle (in radians) between two vectors.
float Vector3::getXAngleWithVector3(const Vector3& v) const
{
    float this_angle = getXAngle();
    float v_angle = v.getXAngle();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}
float Vector3::getYAngleWithVector3(const Vector3& v) const
{
    float this_angle = getYAngle();
    float v_angle = v.getYAngle();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

// Rotates the given vector by the given angle.
void Vector3::rotate(const Vector3& angles) 
{ 
    *this = getRotated(angles);
}
Vector3 Vector3::getRotated(const Vector3& angles) const
{
    return Vector3({ getXAngle() + angles.x, getYAngle() + angles.y, angles.z }, getLength());
}

// Creates a Vector4 from this vector.
Vector4 Vector3::toVector4() const { return Vector4(x, y, z, 1); }




// Calculates linear interpolation for a value from a start point to an end point.
Vector3 Maths::point3Lerp(const float& val, const Vector3& start, const Vector3& end)
{
    return Vector3(lerp(val, start.x, end.x),
                   lerp(val, start.y, end.y),
                   lerp(val, start.z, end.z));
}

// Returns the coordinates of a point on a sphere of radius r, using the given angles.
Vector3 Maths::getSphericalCoords(const float& r, const float& pitch, const float& yaw)
{
    return { r * sinf(pitch) * cosf(yaw),
             r * sinf(pitch) * sinf(yaw),
             r * cosf(pitch) };
}
