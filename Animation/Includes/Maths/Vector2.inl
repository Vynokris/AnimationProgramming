#include "Vector2.h"

// Vector2 equality.
template <typename T>
bool Maths::Vector2::operator==(const T& val) const
{
    return (x == val && y == val);
}
template<>
inline bool Maths::Vector2::operator==<Maths::Vector2>(const Vector2& val) const
{
    return (x == val.x && y == val.y);
}

// Vector2 inequality.
template <typename T>
bool Maths::Vector2::operator!=(const T& val) const
{
    return (x != val || y != val);
}
template<>
inline bool Maths::Vector2::operator!=<Maths::Vector2>(const Vector2& val) const
{
    return (x != val.x || y != val.y);
}

// Vector2 addition.
template <typename T>
Maths::Vector2 Maths::Vector2::operator+(const T& val) const
{
    return Vector2(x + val, y + val);
}
template<>
inline Maths::Vector2 Maths::Vector2::operator+<Maths::Vector2>(const Vector2& val) const
{
    return Vector2(x + val.x, y + val.y);
}

// Vector2 subtraction.
template <typename T>
Maths::Vector2 Maths::Vector2::operator-(const T& val) const
{
    return Vector2(x - val, y - val);
}
template <>
inline Maths::Vector2 Maths::Vector2::operator-<Maths::Vector2>(const Vector2& val) const
{
    return Vector2(x - val.x, y - val.y);
}

// Vector2 multiplication.
template <typename T>
Maths::Vector2 Maths::Vector2::operator*(const T& val) const
{
    return Vector2(x * val, y * val);
}
template <>
inline Maths::Vector2 Maths::Vector2::operator*<Maths::Vector2>(const Vector2& val) const
{
    return Vector2(x * val.x, y * val.y);
}

// Vector2 division.
template <typename T>
Maths::Vector2 Maths::Vector2::operator/(const T& val) const
{
    return Vector2(x / val, y / val);
}
template <>
inline Maths::Vector2 Maths::Vector2::operator/<Maths::Vector2>(const Vector2& val) const
{
    return Vector2(x / val.x, y / val.y);
}

// Vector2 addition assignment.
template <typename T>
void Maths::Vector2::operator+=(const T& val)
{
    x += val;
    y += val;
}
template <>
inline void Maths::Vector2::operator+=<Maths::Vector2>(const Vector2& val)
{
    x += val.x;
    y += val.y;
}

// Vector2 subtraction assignment.
template <typename T>
void Maths::Vector2::operator-=(const T& val)
{
    x -= val;
    y -= val;
}
template <>
inline void Maths::Vector2::operator-=<Maths::Vector2>(const Vector2& val)
{
    x -= val.x;
    y -= val.y;
}

// Vector2 multiplication assignment.
template <typename T>
void Maths::Vector2::operator*=(const T& val)
{
    x *= val;
    y *= val;
}
template <>
inline void Maths::Vector2::operator*=<Maths::Vector2>(const Vector2& val)
{
    x *= val.x;
    y *= val.y;
}

// Vector2 division assignment.
template <typename T>
void Maths::Vector2::operator/=(const T& val)
{
    x /= val;
    y /= val;
}
template <>
inline void Maths::Vector2::operator/=<Maths::Vector2>(const Vector2& val)
{
    x /= val.x;
    y /= val.y;
}
