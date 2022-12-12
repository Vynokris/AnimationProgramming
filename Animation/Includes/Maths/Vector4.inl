#include "Matrix.h"
#include "Vector4.h"
using namespace Maths;

// Vector4 equality.
template <typename T>
inline bool Vector4::operator==(const T& val) const
{
    return (x == val && y == val && z == val && w == val);
}
template<>
inline bool Vector4::operator==<Vector4>(const Vector4& val) const
{
    return (x == val.x && y == val.y && z == val.z && w == val.w);
}

// Vector4 inequality.
template <typename T>
inline bool Vector4::operator!=(const T& val) const
{
    return (x != val || y != val || z != val || w != val);
}
template<>
inline bool Vector4::operator!=<Vector4>(const Vector4& val) const
{
    return (x != val.x || y != val.y || z != val.z || w != val.z);
}

// Vector4 addition.
template <typename T>
inline Vector4 Vector4::operator+(const T& val) const
{
    return Vector4(x + val, y + val, z + val, w + val);
}
template<>
inline Vector4 Vector4::operator+<Vector4>(const Vector4& val) const
{
    return Vector4(x + val.x, y + val.y, z + val.z, w + val.w);
}

// Vector4 substraction.
template <typename T>
inline Vector4 Vector4::operator-(const T& val) const
{
    return Vector4(x - val, y - val, z - val, w - val);
}
template <>
inline Vector4 Vector4::operator-<Vector4>(const Vector4& val) const
{
    return Vector4(x - val.x, y - val.y, z - val.z, w - val.w);
}

// Vector4 multiplication.
template <typename T>
inline Vector4 Vector4::operator*(const T& val) const
{
    return Vector4(x * val, y * val, z * val, w * val);
}

template <>
inline Vector4 Vector4::operator*<Vector4>(const Vector4& val) const
{
    return Vector4(x * val.x, y * val.y, z * val.z, w * val.w);
}

template <>
inline Vector4 Vector4::operator*<Matrix<4,4>>(const Matrix<4,4>& val) const
{
    return Vector4
    (
        x * val[0][0] + y * val[1][0] + z * val[2][0] + w * val[3][0],
        x * val[0][1] + y * val[1][1] + z * val[2][1] + w * val[3][1],
        x * val[0][2] + y * val[1][2] + z * val[2][2] + w * val[3][2],
        x * val[0][3] + y * val[1][3] + z * val[2][3] + w * val[3][3]
    );
}

// Vector4 division.
template <typename T>
inline Vector4 Vector4::operator/(const T& val) const
{
    return Vector4(x / val, y / val, z / val, w / val);
}
template <>
inline Vector4 Vector4::operator/<Vector4>(const Vector4& val) const
{
    return Vector4(x / val.x, y / val.y, z / val.z, w / val.w);
}

// Vector4 addition assignement.
template <typename T>
inline void Vector4::operator+=(const T& val)
{
    x += val;
    y += val;
    z += val;
    w += val;
}
template <>
inline void Vector4::operator+=<Vector4>(const Vector4& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
    w += val.w;
}

// Vector4 substraction assignement.
template <typename T>
inline void Vector4::operator-=(const T& val)
{
    x -= val;
    y -= val;
    z -= val;
    w -= val;
}
template <>
inline void Vector4::operator-=<Vector4>(const Vector4& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
    w -= val.w;
}

// Vector4 multiplication assignement.
template <typename T>
inline void Vector4::operator*=(const T& val)
{
    x *= val;
    y *= val;
    z *= val;
    w *= val;
}
template <>
inline void Vector4::operator*=<Vector4>(const Vector4& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
    w *= val.w;
}

// Vector4 division assignement.
template <typename T>
inline void Vector4::operator/=(const T& val)
{
    x /= val;
    y /= val;
    z /= val;
    w /= val;
}

template <>
inline void Vector4::operator/=<Vector4>(const Vector4& val)
{
    x /= val.x;
    y /= val.y;
    z /= val.z;
    w /= val.w;
}
