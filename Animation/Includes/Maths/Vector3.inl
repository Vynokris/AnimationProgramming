#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
using namespace Maths;

// Vector3 equality.
template <typename T>
inline bool Vector3::operator==(const T& val) const
{
    return (x == val && y == val && z == val);
}
template<>
inline bool Vector3::operator==<Vector3>(const Vector3& val) const
{
    return (x == val.x && y == val.y && z == val.z);
}

// Vector3 inequality.
template <typename T>
inline bool Vector3::operator!=(const T& val) const
{
    return (x != val || y != val || z != val);
}
template<>
inline bool Vector3::operator!=<Vector3>(const Vector3& val) const
{
    return (x != val.x || y != val.y || z != val.z);
}

// Vector3 addition.
template <typename T>
inline Vector3 Vector3::operator+(const T& val) const
{
    return Vector3(x + val, y + val, z + val);
}
template<>
inline Vector3 Vector3::operator+<Vector3>(const Vector3& val) const
{
    return Vector3(x + val.x, y + val.y, z + val.z);
}

// Vector3 subtraction.
template <typename T>
inline Vector3 Vector3::operator-(const T& val) const
{
    return Vector3(x - val, y - val, z - val);
}
template <>
inline Vector3 Vector3::operator-<Vector3>(const Vector3& val) const
{
    return Vector3(x - val.x, y - val.y, z - val.z);
}

// Vector3 multiplication.
template <typename T>
inline Vector3 Vector3::operator*(const T& val) const
{
    return Vector3(x * val, y * val, z * val);
}
template <>
inline Vector3 Vector3::operator*<Vector3>(const Vector3& val) const
{
    return Vector3(x * val.x, y * val.y, z * val.z);
}
template <>
inline Vector3 Vector3::operator*<Matrix<4,4>>(const Matrix<4,4>& val) const
{
    return (ToVector4() * val).ToVector3(true);
}

// Vector3 division.
template <typename T>
inline Vector3 Vector3::operator/(const T& val) const
{
    return Vector3(x / val, y / val, z / val);
}
template <>
inline Vector3 Vector3::operator/<Vector3>(const Vector3& val) const
{
    return Vector3(x / val.x, y / val.y, z / val.z);
}

// Vector3 addition assignment.
template <typename T>
inline void Vector3::operator+=(const T& val)
{
    x += val;
    y += val;
    z += val;
}
template <>
inline void Vector3::operator+=<Vector3>(const Vector3& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
}

// Vector3 subtraction assignment.
template <typename T>
inline void Vector3::operator-=(const T& val)
{
    x -= val;
    y -= val;
    z -= val;
}
template <>
inline void Vector3::operator-=<Vector3>(const Vector3& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
}

// Vector3 multiplication assignment.
template <typename T>
inline void Vector3::operator*=(const T& val)
{
    x *= val;
    y *= val;
    z *= val;
}
template <>
inline void Vector3::operator*=<Vector3>(const Vector3& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
}

// Vector3 division assignment.
template <typename T>
inline void Vector3::operator/=(const T& val)
{
    x /= val;
    y /= val;
    z /= val;
}
template <>
inline void Vector3::operator/=<Vector3>(const Vector3& val)
{
    x /= val.x;
    y /= val.y;
    z /= val.z;
}
