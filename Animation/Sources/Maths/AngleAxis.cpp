#include "Maths/Maths.h"
using namespace Maths;

// ----- Constructors ----- //

AngleAxis::AngleAxis()                                          : angle(0),      axis({ 0 }) {}
AngleAxis::AngleAxis(const float& _angle, const Vector3& _axis) : angle(_angle), axis(_axis.GetNormalized()) {}
AngleAxis::AngleAxis(const Quaternion& quaternion) { *this = quaternion.ToAngleAxis(); }
AngleAxis::AngleAxis(const Mat4&       matrix    ) { *this = matrix    .ToAngleAxis(); }


// ----- Static constructors ----- //

AngleAxis AngleAxis::FromQuaternion(const Quaternion& quaternion) { return quaternion.ToAngleAxis(); }
AngleAxis AngleAxis::FromMatrix    (const Mat4&       matrix    ) { return matrix    .ToAngleAxis(); }


// ----- Conversions ----- //

Quaternion AngleAxis::ToQuaternion() const
{
    const Vector3 nAxis = axis.GetNormalized();
    const float sinTemp = sin(angle/2.f);
    return { cos(angle/2.f), sinTemp*nAxis.x, sinTemp*nAxis.y, sinTemp*nAxis.z };
}

Mat4 AngleAxis::ToMatrix() const
{
    const Vector3 nAxis = axis.GetNormalized();
    const float x = nAxis.x;
    const float y = nAxis.y;
    const float z = nAxis.z;
    const float c = cos(angle);
    const float s = sin(angle);
    return Mat4(sqpow(x)*(1-c)+c, x*y*(1-c)+z*s,    x*z*(1-c)-y*s,    0,
                x*y*(1-c)-z*s,    sqpow(y)*(1-c)+c, y*z*(1-c)+x*s,    0,
                x*z*(1-c)+y*s,    y*z*(1-c)-x*s,    sqpow(z)*(1-c)+c, 0,
                0,                0,                0,                1);
}

std::string AngleAxis::ToString(const int& precision) const
{
    std::ostringstream string;
    string.precision(precision);
    string << std::fixed << angle << ", (" << axis.ToString(precision) << ")";
    return string.str();
}
