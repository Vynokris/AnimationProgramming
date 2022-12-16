#include "Vector4.h"

// Vector4 equality.
template <typename T>
bool Maths::Vector4::operator==(const T& val) const
{
    return (x == val && y == val && z == val && w == val);
}
template<>
inline bool Maths::Vector4::operator==<Maths::Vector4>(const Vector4& val) const
{
    return (x == val.x && y == val.y && z == val.z && w == val.w);
}

// Vector4 inequality.
template <typename T>
bool Maths::Vector4::operator!=(const T& val) const
{
    return (x != val || y != val || z != val || w != val);
}
template<>
inline bool Maths::Vector4::operator!=<Maths::Vector4>(const Vector4& val) const
{
    return (x != val.x || y != val.y || z != val.z || w != val.z);
}

// Vector4 matrix multiplication.
inline Maths::Vector4 Maths::Vector4::operator*(const Mat4& val) const
{
    return Vector4
    (
        x * val[0][0] + y * val[1][0] + z * val[2][0] + w * val[3][0],
        x * val[0][1] + y * val[1][1] + z * val[2][1] + w * val[3][1],
        x * val[0][2] + y * val[1][2] + z * val[2][2] + w * val[3][2],
        x * val[0][3] + y * val[1][3] + z * val[2][3] + w * val[3][3]
    );
}

