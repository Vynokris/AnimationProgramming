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
    return Vector4 (x * val[0][0] + y * val[1][0] + z * val[2][0] + val[3][0],
                    x * val[0][1] + y * val[1][1] + z * val[2][1] + val[3][1],
                    x * val[0][2] + y * val[1][2] + z * val[2][2] + val[3][2],
                    x * val[0][3] + y * val[1][3] + z * val[2][3] + val[3][3]).ToVector3(true);
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
