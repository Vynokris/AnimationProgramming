#pragma once

#ifndef _INCL_MATHLIB_
#define M_VECTOR3D mVector3D::Vector3D

#define M_MIN_FLOAT_VALUE 1.175494351e-38
#define M_MAX_FLOAT_VALUE 3.402823466e+38

// PI VALUES UTILS
#define M_PI 3.141592654f
#define M_2PI 6.283185307f
#define M_1DIVPI 0.318309886f
#define M_1DIV2PI 0.159154943f
#define M_PIDIV2 1.570796327f
#define M_PIDIV4 0.785398163f

#define M_RAD2DEG(rad) ((rad) * 180.0 / M_PI)
#define M_DEG2RAD M_PI/180
#endif

namespace mVector3D
{
    class Vector3D
    {
    public:
        //VECTOR3 MEMBERS
        float x;
        float y;
        float z;

        //VECTOR3 CONSTRUCTORS
        Vector3D(void);
        Vector3D(const float& f);
        Vector3D(const float& x, const float& y, const float& z);

        Vector3D(const Vector3D& v);
        Vector3D(const Vector3D* v);

        //VECTOR3 DESTRUCTOR
        ~Vector3D(void);

        //VECTOR3 UTILS
        Vector3D Normalize    (Vector3D& v);
        Vector3D CrossProduct (const Vector3D& v, const Vector3D& f);
        Vector3D GetVector2pts(const Vector3D& v, const Vector3D& f);
        Vector3D GetNormal    (const Vector3D& v, const Vector3D& f);

        float        GetMagnitude();
        static float DotProduct  (const Vector3D& v, const Vector3D& f);

        //VECTOR3 ASSINGMENT AND EQUALITY OPERATIONS
        inline Vector3D operator =  (const Vector3D& v) { x = v.x; y = v.y; z = v.z; return *this; }
        inline Vector3D operator =  (const float& f)    { x = f; y = f; z = f;       return *this; }
        inline Vector3D operator -  (void)              { x = -x; y = -y; z = -z;    return *this; }

        inline bool     operator == (const Vector3D& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
        inline bool     operator != (const Vector3D& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

        //VECTOR3 ADDITION TO VECTOR3 OPERATION
        inline const Vector3D operator + (const Vector3D& v) const { return Vector3D(x + v.x, y + v.y, z + v.z); }
        inline const Vector3D operator - (const Vector3D& v) const { return Vector3D(x - v.x, y - v.y, z - v.z); }
        inline const Vector3D operator * (const Vector3D& v) const { return Vector3D(x * v.x, y * v.y, z * v.z); }
        inline const Vector3D operator / (const Vector3D& v) const { return Vector3D(x / v.x, y / v.y, z / v.z); }

        //VECTOR3 ADDITION TO THIS OPERATION
        inline Vector3D operator += (const Vector3D& v) { x += v.x; y += v.y; z += v.z; return *this; }
        inline Vector3D operator -= (const Vector3D& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
        inline Vector3D operator *= (const Vector3D& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
        inline Vector3D operator /= (const Vector3D& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

        //FLOAT ADDITION TO VECTOR3 OPERATION
        inline const Vector3D operator + (const float& f) const { return Vector3D(x + f, y + f, z + f); }
        inline const Vector3D operator - (const float& f) const { return Vector3D(x - f, y - f, z - f); }
        inline const Vector3D operator * (const float& f) const { return Vector3D(x * f, y * f, z * f); }
        inline const Vector3D operator / (const float& f) const { return Vector3D(x / f, y / f, z / f); }

        //FLOAT ADDITION TO THIS OPERATION
        inline Vector3D operator += (const float& f) { x += f; y += f; z += f; return *this; }
        inline Vector3D operator -= (const float& f) { x -= f; y -= f; z -= f; return *this; }
        inline Vector3D operator *= (const float& f) { x *= f; y *= f; z *= f; return *this; }
        inline Vector3D operator /= (const float& f) { x /= f; y /= f; z /= f; return *this; }

        inline float operator = (const Vector3D a) const { return { this->x * a.x + this->y * a.y + z * a.z }; }
    };
}