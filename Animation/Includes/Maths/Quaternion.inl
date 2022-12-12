#include "Quaternion.h"
#include "Arithmetic.h"
using namespace Maths;

// Quaternion equality.
template <typename T>
inline bool Quaternion::operator==(const T& val) const
{
    return (w == val && x == val && y == val && z == val);
}
template<>
inline bool Quaternion::operator==<Quaternion>(const Quaternion& val) const
{
    return (w == val.w && x == val.x && y == val.y && z == val.z);
}

// Quaternion inequality.
template <typename T>
inline bool Quaternion::operator!=(const T& val) const
{
    return (w != val || x != val || y != val || z != val);
}
template<>
inline bool Quaternion::operator!=<Quaternion>(const Quaternion& val) const
{
    return (w != val.w || x != val.x || y != val.y || z != val.z);
}

// Quaternion addition.
template <typename T>
inline Quaternion Quaternion::operator+(const T& val) const
{
    return Quaternion(w + val, x + val, y + val, z + val);
}
template<>
inline Quaternion Quaternion::operator+<Quaternion>(const Quaternion& val) const
{
    return Quaternion(w + val.w, x + val.x, y + val.y, z + val.z);
}

// Quaternion substraction.
template <typename T>
inline Quaternion Quaternion::operator-(const T& val) const
{
    return Quaternion(w - val, x - val, y - val, z - val);
}
template <>
inline Quaternion Quaternion::operator-<Quaternion>(const Quaternion& val) const
{
    return Quaternion(w - val.w, x - val.x, y - val.y, z - val.z);
}

// Quaternion multiplication.
template <typename T>
inline Quaternion Quaternion::operator*(const T& val) const
{
    return Quaternion(w * val, x * val, y * val, z * val);
}
template <>
inline Quaternion Quaternion::operator*<Quaternion>(const Quaternion& val) const
{
    return Quaternion(
        w*val.w - x*val.x - y*val.y - z*val.z,
        w*val.x + x*val.w + y*val.z - z*val.y,
        w*val.y - x*val.z + y*val.w + z*val.x,
        w*val.z + x*val.y - y*val.x + z*val.w
    );
}

// Quaternion division.
template <typename T>
inline Quaternion Quaternion::operator/(const T& val) const
{
    return Quaternion(w / val, x / val, y / val, z / val);
}
template <>
inline Quaternion Quaternion::operator/<Quaternion>(const Quaternion& val) const
{
    const float sqAbs = sqpow(val.w) + sqpow(val.x) + sqpow(val.y) + sqpow(val.z);
    return Quaternion(
        (w*val.w + x*val.x + y*val.y + z*val.z) / sqAbs,
        (w*val.x - x*val.w - y*val.z + z*val.y) / sqAbs,
        (w*val.y + x*val.z - y*val.w - z*val.x) / sqAbs,
        (w*val.z - x*val.y + y*val.x - z*val.w) / sqAbs
    );
}

// Quaternion addition assignement.
template <typename T>
inline void Quaternion::operator+=(const T& val)
{
    w += val;
    x += val;
    y += val;
    z += val;
}
template <>
inline void Quaternion::operator+=<Quaternion>(const Quaternion& val)
{
    w += val.w;
    x += val.x;
    y += val.y;
    z += val.z;
}

// Quaternion substraction assignement.
template <typename T>
inline void Quaternion::operator-=(const T& val)
{
    w -= val;
    x -= val;
    y -= val;
    z -= val;
}
template <>
inline void Quaternion::operator-=<Quaternion>(const Quaternion& val)
{
    w -= val.w;
    x -= val.x;
    y -= val.y;
    z -= val.z;
}

// Quaternion multiplication assignement.
template <typename T>
inline void Quaternion::operator*=(const T& val)
{
    w *= val;
    x *= val;
    y *= val;
    z *= val;
}
template <>
inline void Quaternion::operator*=<Quaternion>(const Quaternion& val)
{
    const float _w = w, _x = x, _y = y, _z = z;
    w = _w*val.w - _x*val.x - _y*val.y - _z*val.z;
    x = _w*val.x + _x*val.w + _y*val.z - _z*val.y;
    y = _w*val.y - _x*val.z + _y*val.w + _z*val.x;
    z = _w*val.z + _x*val.y - _y*val.x + _z*val.w;
}

// Quaternion division assignement.
template <typename T>
inline void Quaternion::operator/=(const T& val)
{
    w /= val;
    x /= val;
    y /= val;
    z /= val;
}
template <>
inline void Quaternion::operator/=<Quaternion>(const Quaternion& val)
{
    const float sqAbs = sqpow(val.w) + sqpow(val.x) + sqpow(val.y) + sqpow(val.z);
    const float _w = w, _x = x, _y = y, _z = z;
    w = (_w*val.w + _x*val.x + _y*val.y + _z*val.z) / sqAbs;
    x = (_w*val.x - _x*val.w - _y*val.z + _z*val.y) / sqAbs;
    y = (_w*val.y + _x*val.z - _y*val.w - _z*val.x) / sqAbs;
    z = (_w*val.z - _x*val.y + _y*val.x - _z*val.w) / sqAbs;
}
