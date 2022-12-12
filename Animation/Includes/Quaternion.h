#pragma once

namespace Maths
{
    class Vector3;
    class AngleAxis;
    typedef Matrix<4, 4> Mat4;

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
        float getModulus() const;

        // Returns the argument of the quaternion.
        float getArgument() const;

        // Normalizes this quaternion so that its modulus is 1.
        void normalize();
        Quaternion getNormalized() const;

        // Conjugates the quaternion by inverting the sign of its x, y and z values.
        void conjugate();
        Quaternion getConjugate() const;

        // Inverses the quaternion.
        void inverse();
        Quaternion getInverse() const;

        // Applies this quaternion's rotation to the given object.
        Quaternion rotateQuat(const Quaternion& q) const;
        Vector3    rotateVec (const Vector3&    v) const;

        // Returns the angle-axis rotation that corresponds to this quaternion.
        AngleAxis toAngleAxis() const;
        
        // Returns the rotation matrix that corresponds to this quaternion.
        Mat4 toMatrix() const;
	};
}

#include "Quaternion.inl"