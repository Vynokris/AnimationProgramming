#pragma once

#include <Quaternion.h>

using namespace mQuaternion;

/************************\
 *------QUATERNION------*
\************************/
#pragma region Quaternion
//QUATERNION CONSTRUCTORS
Quaternion::Quaternion(void)														   : w(0), x(0), y(0), z(0) {}
Quaternion::Quaternion(const float& f)												   : w(f), x(f), y(f), z(f) {}
Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z)	 {}
Quaternion::Quaternion(const Quaternion* q) : w(q->w), x(q->x), y(q->y), z(q->z) {}

//VECTOR3 DESTRUCTOR
Quaternion::~Quaternion(void) {}
#pragma endregion