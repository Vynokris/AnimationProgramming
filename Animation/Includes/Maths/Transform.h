#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace Maths
{
    class Transform
    {
	private:
		Vector3    pos;
		Quaternion rot;
    	Vector3    scale;
		bool       isCamera;
		Mat4       localMat, parentMat;

	public:
    	// Constructors.
		Transform(const bool& _isCamera = false);
		Transform(const Vector3& position, const Quaternion& rotation, const Vector3& _scale, const bool& _isCamera = false);

        // Position.
		Vector3 GetPosition() const;                  // Returns the transform's position.
		void    SetPosition(const Vector3& position); // Modifies the transform's position.
		void    Move       (const Vector3& movement); // Adds the given vector to the transform's position.

		// Direction vectors.
		Vector3 Forward() const;                    // Returns the transform's forward vector.
		Vector3 Up     () const;                    // Returns the transform's up vector.
		Vector3 Right  () const;                    // Returns the transform's right vector.
		void    SetForward(const Vector3& forward); // Modifies the transform's rotation to point in the given direction.

		// Rotation.
		Quaternion GetRotation() const;                     // Returns the transform's rotation.
		void       SetRotation(const Quaternion& rotation); // Modified the transform's rotation.
		void       Rotate     (const Quaternion& rotation); // Rotates the transform by the given quaternion.

		// Scale.
		Vector3 GetScale       () const;         // Returns the transform's scale.
		Vector3 GetUniformScale() const;		 // Returns the maximum value between the x, y and z elements of the transform's scale.
		void    SetScale(const Vector3& _scale); // Modifies the transform's scale.

    	// Is camera.
    	bool IsCamera() const;                   // Returns true if the transform is a camera transform, false if it is an object transform.
    	void SetIsCamera(const bool& _isCamera); // Modifies the transform's type (object transform or camera transform).

    	// Multiple values at a time.
    	void SetPosRot(const Vector3& position, const Quaternion& rotation);                        // Modify the transform's position and rotation.
    	void SetValues(const Vector3& position, const Quaternion& rotation, const Vector3& _scale); // Modify all of the transform's values.

		// Matrices.
		Mat4 GetLocalMat () const { return localMat;  }          // Returns the transform's local matrix.
		Mat4 GetParentMat() const { return parentMat; }          // Returns the transform's parent matrix.
    	Mat4 GetWorldMat () const { return localMat * parentMat; } // Returns the transform's world matrix (local * parent).
		void SetParentMat(const Mat4& mat) { parentMat = mat; }    // Modifies the transform's parent matrix.

    	// Interpolation.
    	static Transform Lerp(const Transform& start, const Transform& dest, const float& val, const bool& useSlerp = true); // Linearly interpolates between start and dest.

	private:
		void UpdateLocalMat();
    };
}