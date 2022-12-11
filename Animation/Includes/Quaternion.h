#pragma once

namespace Maths
{
    // Quaternion class that holds values for w, x, y and z (4 dimensions of rotation).
	class Quaternion
	{
	public:
		float w;
		float x;
		float y;
		float z;
        
        // -- Constructors & Destructor -- //
		Quaternion();                                                               // Null quaternion.
		Quaternion(const float& all);                                               // Quaternion with equal values.
		Quaternion(const float& w, const float& x, const float& y, const float& z); // Quaternion with 4 values.
		Quaternion(const Quaternion& q);
		~Quaternion() {}

        // -- Operators -- //
                              void       operator= (const Quaternion& q);
        template <typename T> bool       operator==(const T& val) const;
        template <typename T> bool       operator!=(const T& val) const;
        template <typename T> Quaternion operator+ (const T& val) const;
        template <typename T> Quaternion operator- (const T& val) const;
        template <typename T> Quaternion operator* (const T& val) const;
        template <typename T> Quaternion operator/ (const T& val) const;
        template <typename T> void       operator+=(const T& val);
        template <typename T> void       operator-=(const T& val);
        template <typename T> void       operator*=(const T& val);
        template <typename T> void       operator/=(const T& val);
                              Quaternion operator- ()                    const;
        
        // -- Methods -- //
        
        // Returns the absolute value of the quaternion.
        float getAbs();

        // Returns the argument of the quaternion.
        float getArg();

        // Conjugates the quaternion by inverting the sign of its x, y and z values.
        void conjugate();
        Quaternion getConjugate();

        // Inverses the quaternion.
        void inverse();
        Quaternion getInverse();
	};
}

#include "Quaternion.inl"