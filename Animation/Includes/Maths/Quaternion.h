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
        
        // -- Constructors -- //
		Quaternion();                                                               // Null quaternion.
		Quaternion(const float& all);                                               // Quaternion with equal values.
		Quaternion(const float& w, const float& x, const float& y, const float& z); // Quaternion with 4 values.
		Quaternion(const Vector3&   eulerAngles);                                   // Quaternion from euler angles (pitch, roll, yaw).
		Quaternion(const AngleAxis& angleAxis  );                                   // Quaternion from angle axis.
		Quaternion(const Mat4&      matrix     );                                   // Quaternion from 4x4 matrix.

		// -- Static constructors -- //
		static Quaternion FromPitch    (const float&     angle    ); // Quaternion that rotates around the X axis by the given angle.
		static Quaternion FromRoll     (const float&     angle    ); // Quaternion that rotates around the Y axis by the given angle.
		static Quaternion FromYaw      (const float&     angle    ); // Quaternion that rotates around the Z axis by the given angle.
		static Quaternion FromEuler    (const Vector3&   angles   ); // Quaternion from euler angles (pitch, roll, yaw).
		static Quaternion FromAngleAxis(const AngleAxis& angleAxis); // Quaternion from angle axis.
		static Quaternion FromMatrix   (const Mat4&      matrix   ); // Quaternion from 4x4 matrix.

		// -- Operators -- //
        template <typename T> bool       operator==(const T& val) const;
        template <typename T> bool       operator!=(const T& val) const;
        template <typename T> Quaternion operator+ (const T& val) const;
                              Quaternion operator- (            ) const;
        template <typename T> Quaternion operator- (const T& val) const;
        template <typename T> Quaternion operator* (const T& val) const;
        template <typename T> Quaternion operator/ (const T& val) const;
        template <typename T> void       operator+=(const T& val);
        template <typename T> void       operator-=(const T& val);
        template <typename T> void       operator*=(const T& val);
		template <typename T> void       operator/=(const T& val);
							  float      Dot       (const Quaternion& q) const;
        
        // -- Methods -- //
        
        // Returns the absolute value of the quaternion.
        float GetModulus() const;

		// Normalization.
        void       Normalize();           // Normalizes this quaternion so that its modulus is 1.
        Quaternion GetNormalized() const; // Returns a normalized copy of the quaternion.

		// Conjugation.
        void       Conjugate();          // Conjugates the quaternion by inverting the sign of its x, y and z values.
        Quaternion GetConjugate() const; // Returns the conjugate of the quaternion.

		// Inversion.
        void       Inverse();          // Inverses the quaternion.
        Quaternion GetInverse() const; // Returns the inverse of the quaternion.

		// Rotation.
        Quaternion RotateQuat(const Quaternion& q) const; // Applies this quaternion's rotation to the given quaternion.
        Vector3    RotateVec (const Vector3&    v) const; // Applies this quaternion's rotation to the given 3D vector.

		// Interpolation.
		static Quaternion Lerp (const Quaternion& start, const Quaternion& dest, const float& val);                                     // Interpolates between start and dest without normalizing the output.
		static Quaternion NLerp(const Quaternion& start, const Quaternion& dest, const float& val);                                     // Normalized interpolation of start and dest.
		static Quaternion SLerp(const Quaternion& start, const Quaternion& dest, const float& val, const bool& useShortestPath = true); // Spherical interpolation of start and dest.

		// Conversion.
        AngleAxis   ToAngleAxis()                      const; // Returns the angle-axis rotation that corresponds to this quaternion.
        Mat4        ToMatrix()                         const; // Returns the rotation matrix that corresponds to this quaternion.
		Vector3     ToEuler ()                         const; // Returns the euler angles that correspond to this quaternion.
		std::string ToString(const int& precision = 2) const; // Returns the quaternion's contents as a string.
	};
}

#include "Quaternion.inl"