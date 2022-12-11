#pragma once

#include <cmath>

#include <Vector3D.h>

using namespace mVector3D;

/************************\
 *-------VECTOR_3-------*
\************************/
#pragma region Vector3D
//VECTOR3 CONSTRUCTORS
Vector3D::Vector3D(void)										   : x(0), y(0), z(0) {}
Vector3D::Vector3D(const float& f)								   : x(f), y(f), z(f) {}
Vector3D::Vector3D(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}

Vector3D::Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z)    {}
Vector3D::Vector3D(const Vector3D* v) : x(v->x), y(v->y), z(v->z) {}

//VECTOR3 DESTRUCTOR
Vector3D::~Vector3D(void) {}

//VECTOR3 UTILS
Vector3D Vector3D::Normalize    (Vector3D& v)						   {				 return v     = { v.x / GetMagnitude(), v.y / GetMagnitude(), v.z / GetMagnitude()	  }; }
Vector3D Vector3D::CrossProduct (const Vector3D& v, const Vector3D& f) { Vector3D cross; return cross = { v.y * f.z - v.z * f.y, v.z * f.x - v.x * f.z, v.x * f.y - v.y * f.x }; }
Vector3D Vector3D::GetVector2pts(const Vector3D& v, const Vector3D& f) { Vector3D vec;	 return vec   = { v.x - f.x, v.y - f.y, v.z - f.z									  }; }
Vector3D Vector3D::GetNormal    (const Vector3D& v, const Vector3D& f) { Vector3D norm;  return norm  = { v.y * f.z - v.z * f.y, v.z * f.x - v.x * f.z, v.x * v.y - f.x * f.y }; }

float Vector3D::GetMagnitude()									 {			  return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
float Vector3D::DotProduct(const Vector3D& v, const Vector3D& f) { float res; return res = { v.x * f.x + v.y * f.y + v.z * f.z}    ; }
#pragma endregion
