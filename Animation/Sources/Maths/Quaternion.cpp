#include "Maths/Maths.h"
using namespace Maths;


// ---------- QUATERNION OPERATORS & CONSTRUCTORS ---------- //

// Constructors.
Quaternion::Quaternion()                                                               : w(0),   x(0),   y(0),   z(0)   {}
Quaternion::Quaternion(const float& all)                                               : w(all), x(all), y(all), z(all) {}
Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) : w(w),   x(x),   y(y),   z(z)   {}

// Quaternion negation.
Quaternion Quaternion::operator-() const { return { -w, -x, -y, -z }; }


// ---------- QUATERNION METHODS ---------- //

// Returns the absolute value of the quaternion.
float Quaternion::GetModulus() const
{
    return sqrt(sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z));
}

// Returns the argument of the quaternion.
float Quaternion::GetArgument() const // TODO: Test this.
{
    return acos(w / GetModulus());
}

// Normalization.
void Quaternion::Normalize()
{
    *this = GetNormalized();
}
Quaternion Quaternion::GetNormalized() const
{
    const float modulus = GetModulus();
    return Quaternion(w/modulus, x/modulus, y/modulus, z/modulus);
}

// Conjugation.
void       Quaternion::Conjugate   ()       { x *= -1; y *= -1; z *= -1; }
Quaternion Quaternion::GetConjugate() const { return { w, -x, -y, -z }; }

// Inversion.
void Quaternion::Inverse()
{
    *this = GetInverse();
}
Quaternion Quaternion::GetInverse() const // TODO: Test this.
{
    const float sqAbs = sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z);
    return Quaternion(w / sqAbs, -x / sqAbs, -y / sqAbs, -z / sqAbs);
}

// Rotation.
Quaternion Quaternion::RotateQuat(const Quaternion& q) const // TODO: Test this.
{
    return q * *this;
}
Vector3 Quaternion::RotateVec(const Vector3& v) const // TODO: Test this.
{
    const Quaternion rotatedVec = RotateQuat({ 0, v.x, v.y, v.z });
    return Vector3(rotatedVec.x, rotatedVec.y, rotatedVec.z);
}

// Returns the angle-axis rotation that corresponds to this quaternion.
AngleAxis Quaternion::ToAngleAxis() const // TODO: Test this.
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

// Returns the rotation matrix that corresponds to this quaternion.
Mat4 Quaternion::ToMatrix() const // TODO: Test this.
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

// Returns the euler angles that correspond to this quaternion.
Vector3 Quaternion::ToEuler() const // TODO: Test this.
{
    return Vector3(
        atan2(2*(w*x+y*z), 1-2*(sqpow(w)+sqpow(x))),
        asin(2*(w*y-z*x)),
        atan2(2*(w*z+x*y), 1-2*(sqpow(y)+sqpow(z)))
    );
}

// Returns the quaternion's contents as a string.
std::string Quaternion::ToString(const int& precision) const
{
    std::ostringstream string;
    string.precision(precision);
    string << std::fixed << w << ", " << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z;
    return string.str();
}
