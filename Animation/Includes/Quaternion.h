#pragma once

#ifndef _INCL_MATHLIB_
#define M_QUATERNION mQuaternion::Quaternion
#endif

namespace mQuaternion
{
	class Quaternion
	{
	public:
		//QUATERNION MEMBERS
		float w;
		float x;
		float y;
		float z;

		//QUATERNION CONSTRUCTORS
		Quaternion(void);
		Quaternion(const float& f);
		Quaternion(const float& w, const float& x, const float& y, const float& z);

		Quaternion(const Quaternion& q);
		Quaternion(const Quaternion* q);

		//VECTOR3 DESTRUCTOR
		~Quaternion(void);
	};
}