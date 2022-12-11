#include "Vector3.h"
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

// Vector3 substraction.
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

// Vector3 addition assignement.
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

// Vector3 substraction assignement.
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

// Vector3 multiplication assignement.
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

// Vector3 division assignement.
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
