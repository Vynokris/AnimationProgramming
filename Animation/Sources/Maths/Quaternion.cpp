#include "Maths/Maths.h"
using namespace Maths;


// ---------- QUATERNION OPERATORS & CONSTRUCTORS ---------- //

// Constructors.
Quaternion::Quaternion()                                                               : w(0),   x(0),   y(0),   z(0)   {}
Quaternion::Quaternion(const float& all)                                               : w(all), x(all), y(all), z(all) {}
Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) : w(w),   x(x),   y(y),   z(z)   {}
Quaternion::Quaternion(const Quaternion& q)                                            : w(q.w), x(q.x), y(q.y), z(q.z) {}

// Copy constructor.
void Quaternion::operator=(const Quaternion& q) { w = q.w; x = q.x; y = q.y; z = q.z; }

// Quaternion negation.
Quaternion Quaternion::operator-() const { return { -w, -x, -y, -z }; }


// ---------- QUATERNION METHODS ---------- //

float Quaternion::getModulus() const
{
    return sqrt(sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z));
}

float Quaternion::getArgument() const
{
    return acos(w / getModulus());
}

void Quaternion::normalize()
{
    *this = getNormalized();
}

Quaternion Quaternion::getNormalized() const
{
    const float modulus = getModulus();
    return Quaternion(w/modulus, x/modulus, y/modulus, z/modulus);
}

void Quaternion::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::getConjugate() const
{
    return Quaternion(w, -x, -y, -z);
}

void Quaternion::inverse()
{
    *this = getInverse();
}

Quaternion Quaternion::getInverse() const
{
    const float sqAbs = sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z);
    return Quaternion(w / sqAbs, -x / sqAbs, -y / sqAbs, -z / sqAbs);
}


Quaternion Quaternion::rotateQuat(const Quaternion& q) const
{
    return q * *this; // TODO: Idk if this works.
}

Vector3 Quaternion::rotateVec(const Vector3& v) const
{
    const Quaternion rotatedVec = rotateQuat({ 0, v.x, v.y, v.z });
    return { rotatedVec.x, rotatedVec.y, rotatedVec.z };
}

AngleAxis Quaternion::toAngleAxis() const
{
    const float angle = 2 * acos(w);
    return AngleAxis(
        angle,
        {
            x / sin(angle/2),
            y / sin(angle/2),
            z / sin(angle/2)
        }
    );
}

Mat4 Quaternion::toMatrix() const
{
    const float w2 = sqpow(w);
    const float x2 = sqpow(x);
    const float y2 = sqpow(y);
    const float z2 = sqpow(z);
    return Mat4(
        2*(w2+x2)-1, 2*(x*y+z*w), 2*(x*z-y*w), 0,
        2*(x*y-z*w), 2*(w2+y2)-1, 2*(y*z+x*w), 0,
        2*(x*z+y*w), 2*(y*z-x*w), 2*(w2+z2)-1, 0,
        0,           0,           0,           1
    );
}

Vector3 Maths::Quaternion::toEuler() const
{
    return Vector3(
        atan2(2*(w*x+y*z), 1-2*(sqpow(w)+sqpow(x))),
        asin(2*(w*y-z*x)),
        atan2(2*(w*z+x*y), 1-2*(sqpow(y)+sqpow(z)))
    );
}
