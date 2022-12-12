#include "Maths/Maths.h"
using namespace Maths;


// ---------- ANGLE-AXIS METHODS ---------- //

AngleAxis::AngleAxis()                                          : angle(0),      axis({ 0 }) {}
AngleAxis::AngleAxis(const float& _angle, const Vector3& _axis) : angle(_angle), axis(_axis) {}

Quaternion AngleAxis::ToQuaternion() // TODO: To test.
{
    axis.Normalize();
    const float sinTemp = sin(angle/2.f);
    return { cos(angle/2.f), sinTemp*axis.x, sinTemp*axis.y, sinTemp*axis.z };
}

Mat4 AngleAxis::ToMatrix() // TODO: To test.
{
    axis.Normalize();
    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;
    const float c = cos(angle);
    const float s = sin(angle);
    return Mat4(sqpow(x)*(1-c)+c, x*y*(1-c)-z*s,    x*z*(1-c)+y*s,    0,
                x*y*(1-c)+z*s,    sqpow(y)*(1-c)+c, y*z*(1-c)-x*s,    0,
                x*z*(1-c)-y*s,    y*z*(1-c)+x*s,    sqpow(z)*(1-c)+c, 0,
                0,                0,                0,                1);
}