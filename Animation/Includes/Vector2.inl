#include "Vector2.h"
using namespace Maths;

// Vector2 equality.
template <typename T>
inline bool Vector2::operator==(const T& val) const
{
    return (x == val && y == val);
}
template<>
inline bool Vector2::operator==<Vector2>(const Vector2& val) const
{
    return (x == val.x && y == val.y);
}

// Vector2 inequality.
template <typename T>
inline bool Vector2::operator!=(const T& val) const
{
    return (x != val || y != val);
}
template<>
inline bool Vector2::operator!=<Vector2>(const Vector2& val) const
{
    return (x != val.x || y != val.y);
}

// Vector2 addition.
template <typename T>
inline Vector2 Vector2::operator+(const T& val) const
{
    return Vector2(x + val, y + val);
}
template<>
inline Vector2 Vector2::operator+<Vector2>(const Vector2& val) const
{
    return Vector2(x + val.x, y + val.y);
}

// Vector2 substraction.
template <typename T>
inline Vector2 Vector2::operator-(const T& val) const
{
    return Vector2(x - val, y - val);
}
template <>
inline Vector2 Vector2::operator-<Vector2>(const Vector2& val) const
{
    return Vector2(x - val.x, y - val.y);
}

// Vector2 multiplication.
template <typename T>
inline Vector2 Vector2::operator*(const T& val) const
{
    return Vector2(x * val, y * val);
}
template <>
inline Vector2 Vector2::operator*<Vector2>(const Vector2& val) const
{
    return Vector2(x * val.x, y * val.y);
}

// Vector2 division.
template <typename T>
inline Vector2 Vector2::operator/(const T& val) const
{
    return Vector2(x / val, y / val);
}
template <>
inline Vector2 Vector2::operator/<Vector2>(const Vector2& val) const
{
    return Vector2(x / val.x, y / val.y);
}

// Vector2 addition assignement.
template <typename T>
inline void Vector2::operator+=(const T& val)
{
    x += val;
    y += val;
}
template <>
inline void Vector2::operator+=<Vector2>(const Vector2& val)
{
    x += val.x;
    y += val.y;
}

// Vector2 substraction assignement.
template <typename T>
inline void Vector2::operator-=(const T& val)
{
    x -= val;
    y -= val;
}
template <>
inline void Vector2::operator-=<Vector2>(const Vector2& val)
{
    x -= val.x;
    y -= val.y;
}

// Vector2 multiplication assignement.
template <typename T>
inline void Vector2::operator*=(const T& val)
{
    x *= val;
    y *= val;
}
template <>
inline void Vector2::operator*=<Vector2>(const Vector2& val)
{
    x *= val.x;
    y *= val.y;
}

// Vector2 division assignement.
template <typename T>
inline void Vector2::operator/=(const T& val)
{
    x /= val;
    y /= val;
}
template <>
inline void Vector2::operator/=<Vector2>(const Vector2& val)
{
    x /= val.x;
    y /= val.y;
}