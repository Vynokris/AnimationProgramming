#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"

// Vector3 equality.
template <typename T>
bool Maths::Vector3::operator==(const T& val) const
{
    return (x == val && y == val && z == val);
}
template<>
inline bool Maths::Vector3::operator==<Maths::Vector3>(const Vector3& val) const
{
    return (x == val.x && y == val.y && z == val.z);
}

// Vector3 inequality.
template <typename T>
bool Maths::Vector3::operator!=(const T& val) const
{
    return (x != val || y != val || z != val);
}
template<>
inline bool Maths::Vector3::operator!=<Maths::Vector3>(const Vector3& val) const
{
    return (x != val.x || y != val.y || z != val.z);
}

// Vector3 addition.
template <typename T>
Maths::Vector3 Maths::Vector3::operator+(const T& val) const
{
    return Vector3(x + val, y + val, z + val);
}
template<>
inline Maths::Vector3 Maths::Vector3::operator+<Maths::Vector3>(const Vector3& val) const
{
    return Vector3(x + val.x, y + val.y, z + val.z);
}

// Vector3 subtraction.
template <typename T>
Maths::Vector3 Maths::Vector3::operator-(const T& val) const
{
    return Vector3(x - val, y - val, z - val);
}
template <>
inline Maths::Vector3 Maths::Vector3::operator-<Maths::Vector3>(const Vector3& val) const
{
    return Vector3(x - val.x, y - val.y, z - val.z);
}

// Vector3 multiplication.
template <typename T>
Maths::Vector3 Maths::Vector3::operator*(const T& val) const
{
    return Vector3(x * val, y * val, z * val);
}
template <>
inline Maths::Vector3 Maths::Vector3::operator*<Maths::Vector3>(const Vector3& val) const
{
    return Vector3(x * val.x, y * val.y, z * val.z);
}
template <>
inline Maths::Vector3 Maths::Vector3::operator*<Maths::Matrix<4,4>>(const Matrix<4,4>& val) const
{
    return (ToVector4() * val).ToVector3(true);
}

// Vector3 division.
template <typename T>
Maths::Vector3 Maths::Vector3::operator/(const T& val) const
{
    return Vector3(x / val, y / val, z / val);
}
template <>
inline Maths::Vector3 Maths::Vector3::operator/<Maths::Vector3>(const Vector3& val) const
{
    return Vector3(x / val.x, y / val.y, z / val.z);
}

// Vector3 addition assignment.
template <typename T>
void Maths::Vector3::operator+=(const T& val)
{
    x += val;
    y += val;
    z += val;
}
template <>
inline void Maths::Vector3::operator+=<Maths::Vector3>(const Vector3& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
}

// Vector3 subtraction assignment.
template <typename T>
void Maths::Vector3::operator-=(const T& val)
{
    x -= val;
    y -= val;
    z -= val;
}
template <>
inline void Maths::Vector3::operator-=<Maths::Vector3>(const Vector3& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
}

// Vector3 multiplication assignment.
template <typename T>
void Maths::Vector3::operator*=(const T& val)
{
    x *= val;
    y *= val;
    z *= val;
}
template <>
inline void Maths::Vector3::operator*=<Maths::Vector3>(const Vector3& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
}

// Vector3 division assignment.
template <typename T>
void Maths::Vector3::operator/=(const T& val)
{
    x /= val;
    y /= val;
    z /= val;
}
template <>
inline void Maths::Vector3::operator/=<Maths::Vector3>(const Vector3& val)
{
    x /= val.x;
    y /= val.y;
    z /= val.z;
}
