#pragma once

#include "Matrix.h"
#include "Vector3.h"

namespace Maths
{
    class Transform
    {
	private:
		Maths::Vector3 pos, rot, scale;
		Maths::Mat4 modelMat;

	public:
		Maths::Mat4 parentMat = Maths::Mat4(true);
		bool isCamera = false;
		Transform(bool _isCamera = false);

        // Position.
		Maths::Vector3 GetPosition() const;
		void SetPosition(const Maths::Vector3& position);
		void Move(const Maths::Vector3& movement);

		// Forward.
		Maths::Vector3 Forward() const;
		Maths::Vector3 Up()      const;
		Maths::Vector3 Right()   const;
		void SetForward(const Maths::Vector3& forward);

		// Rotation.
		Maths::Vector3 GetRotation() const;
		void SetRotation(const Maths::Vector3& rotation);
		void Rotate(const Maths::Vector3& rotation);

		// Scale.
		Maths::Vector3 GetScale() const;
		Maths::Vector3 GetUniformScale() const;
		void SetScale(const Maths::Vector3& _scale);

		// Matrices.
		Maths::Mat4 GetModelMat() const;

	private:
		void UpdateModelMat();
    };
}