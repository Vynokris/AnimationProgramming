#include "Maths/Maths.h"
using namespace Maths;


// ---------- QUATERNION OPERATORS & CONSTRUCTORS ---------- //

// Constructors.
Quaternion::Quaternion()                                                               : w(0),   x(0),   y(0),   z(0)   {}
Quaternion::Quaternion(const float& all)                                               : w(all), x(all), y(all), z(all) {}
Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) : w(w),   x(x),   y(y),   z(z)   {}
Quaternion::Quaternion(const Vector3& eulerAngles)                                     : w(0),   x(0),   y(0),   z(0)
{
    const float cX = cos(eulerAngles.x * 0.5f), sX = sin(eulerAngles.x * 0.5f);
    const float cY = cos(eulerAngles.y * 0.5f), sY = sin(eulerAngles.y * 0.5f);
    const float cZ = cos(eulerAngles.z * 0.5f), sZ = sin(eulerAngles.z * 0.5f);

    w = cX*cY*cZ + sX*sY*sZ;
    x = sX*cY*cZ - cX*sY*sZ;
    y = cX*sY*cZ + sX*cY*sZ;
    z = cX*cY*sZ - sX*sY*cZ;
}

// Quaternion negation.
Quaternion Quaternion::operator-() const { return { -w, -x, -y, -z }; }


// ---------- QUATERNION METHODS ---------- //

// Returns the absolute value of the quaternion.
float Quaternion::GetModulus() const
{
    return sqrt(sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z));
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
Quaternion Quaternion::GetInverse() const
{
    const float sqAbs = sqpow(w) + sqpow(x) + sqpow(y) + sqpow(z);
    return Quaternion(w / sqAbs, -x / sqAbs, -y / sqAbs, -z / sqAbs);
}

// Rotation.
Quaternion Quaternion::RotateQuat(const Quaternion& q) const
{
    return *this * q;
}
Vector3 Quaternion::RotateVec(const Vector3& v) const
{
    const Quaternion vecQuat = { 0, v.x, v.y, v.z };
    const Quaternion rotated = *this * vecQuat * GetInverse();
    return { rotated.x, rotated.y, rotated.z };
}

// Interpolation.
Quaternion Quaternion::Lerp(const Quaternion& start, const Quaternion& dest, const float& t)
{
    return Quaternion(lerp(t, start.w, dest.w),
                      lerp(t, start.x, dest.x),
                      lerp(t, start.y, dest.y),
                      lerp(t, start.z, dest.z));
}

Quaternion Quaternion::NLerp(const Quaternion& start, const Quaternion& dest, const float& t)
{
    return Lerp(start, dest, t).GetNormalized();
}

Quaternion Quaternion::SLerp(const Quaternion& start, const Quaternion& dest, const float& t)
{
    const float theta = acos(start.x*dest.x + start.y*dest.y + start.z*dest.z + start.w*dest.w);
    const float sn    = sin(theta);
    const float Wa    = sin((1-t)*theta) / sn;
    const float Wb    = sin(t*theta) / sn;
    return Quaternion(Wa * start.w + Wb * dest.w,
                      Wa * start.x + Wb * dest.x,
                      Wa * start.y + Wb * dest.y,
                      Wa * start.z + Wb * dest.z).GetNormalized();
}

// Returns the angle-axis rotation that corresponds to this quaternion.
AngleAxis Quaternion::ToAngleAxis() const
{
    const float angle = 2 * acos(w);
    AngleAxis angleAxis;
    if (angle == 0.f || angle == PI) angleAxis = AngleAxis(angle, Vector3(x, y, z).GetNormalized());
    else                             angleAxis = AngleAxis(angle, Vector3(x, y, z) / sin(angle/2));
    return angleAxis;
}

// Returns the rotation matrix that corresponds to this quaternion.
Mat4 Quaternion::ToMatrix() const
{
    const float w2 = sqpow(w);
    const float x2 = sqpow(x);
    const float y2 = sqpow(y);
    const float z2 = sqpow(z);
    return Mat4(2*(w2+x2)-1, 2*(x*y+z*w), 2*(x*z-y*w), 0,
                2*(x*y-z*w), 2*(w2+y2)-1, 2*(y*z+x*w), 0,
                2*(x*z+y*w), 2*(y*z-x*w), 2*(w2+z2)-1, 0,
                0,           0,           0,           1);
}

// Returns the euler angles that correspond to this quaternion.
Vector3 Quaternion::ToEuler() const
{
    Vector3 eulerAngles;

    // X-axis rotation (roll).
    const float sinX_cosY = 2 * (w * x + y * z);
    const float cosX_cosY = 1 - 2 * (x * x + y * y);
    eulerAngles.x = std::atan2(sinX_cosY, cosX_cosY);

    // Y-axis rotation (pitch).
    const float sinX = 2 * (w * y - z * x);
    if (std::abs(sinX) >= 1) eulerAngles.y = std::copysign(PI/2, sinX); // Use 90 degrees if out of range.
    else                     eulerAngles.y = std::asin(sinX);

    // Z-axis rotation (yaw).
    const float sinZ_cosY = 2 * (w * z + x * y);
    const float cosZ_cosY = 1 - 2 * (y * y + z * z);
    eulerAngles.z = std::atan2(sinZ_cosY, cosZ_cosY);

    return eulerAngles;
}

// Returns the quaternion's contents as a string.
std::string Quaternion::ToString(const int& precision) const
{
    std::ostringstream string;
    string.precision(precision);
    string << std::fixed << w << ", " << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z;
    return string.str();
}
