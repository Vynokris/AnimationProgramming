#pragma once

#include "Maths.h"
using namespace Maths;

// Constructors.
Quaternion::Quaternion()                                                               : w(0),   x(0),   y(0),   z(0)   {}
Quaternion::Quaternion(const float& all)                                               : w(all), x(all), y(all), z(all) {}
Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) : w(w),   x(x),   y(y),   z(z)   {}
Quaternion::Quaternion(const Quaternion& q)                                            : w(q.w), x(q.x), y(q.y), z(q.z) {}


// ---------- VECTOR3 OPERATORS ---------- //

// Copy constructor.
void Quaternion::operator=(const Quaternion& q) { w = q.w; x = q.x; y = q.y; z = q.z; }

// Quaternion negation.
Quaternion Quaternion::operator-() const { return { -w, -x, -y, -z }; }


// ---------- VECTOR3 METHODS ---------- //

float Maths::Quaternion::getAbs()
{
    return sqrt(sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z));
}

float Maths::Quaternion::getArg()
{
    return 0; // I don't know lmao
}

void Maths::Quaternion::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Maths::Quaternion::getConjugate()
{
    return Quaternion(w, -x, -y, -z);
}

void Maths::Quaternion::inverse()
{
    *this = getInverse();
}

Quaternion Maths::Quaternion::getInverse()
{
    const float sqAbs = sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z);
    return Quaternion(w / sqAbs, -x / sqAbs, -y / sqAbs, -z / sqAbs);
}
