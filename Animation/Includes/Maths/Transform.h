#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace Maths
{
    class Transform
    {
	private:
		Vector3 pos, scale;
		Quaternion rot;
		Mat4 localMat;

	public:
		Mat4 worldMat;
		bool isCamera;
		Transform(const bool& _isCamera = false);
		Transform(const Vector3& _pos, const Quaternion& _rot, const Vector3& _scale, const bool& _isCamera = false);

        // Position.
		Vector3 GetPosition() const;
		void SetPosition(const Vector3& position);
		void Move(const Vector3& movement);

		// Forward.
		Vector3 Forward() const;
		Vector3 Up()      const;
		Vector3 Right()   const;
		void SetForward(const Vector3& forward);

		// Rotation.
		Quaternion GetRotation() const;
		void SetRotation(const Quaternion& rotation);
		void Rotate     (const Quaternion& rotation);

		// Scale.
		Vector3 GetScale() const;
		Vector3 GetUniformScale() const;
		void SetScale(const Vector3& _scale);

		// Matrices.
		Mat4 GetLocalMat() const;

	private:
		void UpdateLocalMat();
    };
}