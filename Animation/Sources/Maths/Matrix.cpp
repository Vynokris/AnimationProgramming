#include "Maths/Maths.h"


// ---------- MATRIX GLOBAL METHODS ---------- //

Mat4 Maths::GetTranslationMatrix(const Vector3& translation)
{
    return Mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                translation.x, translation.y, translation.z, 1);
}

Mat4 Maths::GetXRotationMatrix(const float& angle)
{
    return AngleAxis(angle, { 1, 0, 0 }).ToMatrix();
}

Mat4 Maths::GetYRotationMatrix(const float& angle)
{
    return AngleAxis(angle, { 0, 1, 0 }).ToMatrix();
}

Mat4 Maths::GetZRotationMatrix(const float& angle)
{
    return AngleAxis(angle, { 0, 0, 1 }).ToMatrix();
}

Mat4 Maths::GetRotationMatrix(const Vector3& rotation, const bool& reverse)
{
    // For cameras.
    if (reverse)
        return Quaternion(rotation).ToMatrix().Inv4(); // TODO: Untested.

    // For objects in world space.
    return Quaternion(rotation).ToMatrix();
}

Mat4 Maths::GetScaleMatrix(const Vector3& scale)
{
    return Mat4(scale.x, 0, 0, 0,
                0, scale.y, 0, 0,
                0, 0, scale.z, 0,
                0, 0, 0, 1);
}

Mat4 Maths::GetTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse, const bool& transformNormals)
{
    // For cameras.
    if (reverse)
    {
        return GetTranslationMatrix(position)          *
               GetRotationMatrix   (rotation, reverse) * 
               GetScaleMatrix      (scale);
    }
    
    // For normals.
    if (transformNormals)
    {
        return GetTransformMatrix(position, rotation, scale).Inv4().GetTransposed();
    }
    
    // For objects in world space.
    return GetScaleMatrix      (scale)             *
           GetRotationMatrix   (rotation, reverse) * 
           GetTranslationMatrix(position);
}

Mat4 Maths::GetTransformMatrix(const Vector3& position, const Quaternion& rotation, const Vector3& scale, const bool& reverse, const bool& transformNormals)
{
    // For cameras.
    if (reverse)
    {
        return GetTranslationMatrix(position) *
               rotation.ToMatrix   ()         *
               GetScaleMatrix      (scale);
    }
    
    // For normals.
    if (transformNormals)
    {
        return GetTransformMatrix(position, rotation, scale).Inv4().GetTransposed();
    }
    
    // For objects in world space.
    return GetScaleMatrix      (scale) *
           rotation.ToMatrix   ()      *
           GetTranslationMatrix(position);
}
