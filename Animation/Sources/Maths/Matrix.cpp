#include "Maths/Maths.h"


// ---------- MATRIX GLOBAL METHODS ---------- //

Mat4 Maths::GetTranslationMatrix(const Vector3& translation)
{
    return Mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -translation.x, translation.y, translation.z, 1);
}

Mat4 Maths::GetXRotationMatrix(const float& angle)
{
    return Mat4(1, 0, 0, 0,
                0, cosf(angle), sinf(angle), 0,
                0, -sinf(angle), cosf(angle), 0,
                0, 0, 0, 1);
}

Mat4 Maths::GetYRotationMatrix(const float& angle)
{
    return Mat4(cosf(angle), 0, -sinf(angle), 0,
                0, 1, 0, 0,
                sinf(angle), 0, cosf(angle), 0,
                0, 0, 0, 1);
}

Mat4 Maths::GetZRotationMatrix(const float& angle)
{
    return Mat4(cosf(angle), sinf(angle), 0, 0,
                -sinf(angle), cosf(angle), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

Mat4 Maths::GetRotationMatrix(const Vector3& rotation, const bool& reverse)
{
    // For cameras.
    if (reverse)
    {
        return GetYRotationMatrix(rotation.y) *
               GetXRotationMatrix(-rotation.x) *
               GetZRotationMatrix(rotation.z);
    }
    // For objects in world space.
    else
    {
        return GetZRotationMatrix(rotation.z) *
               GetXRotationMatrix(-rotation.x) *
               GetYRotationMatrix(rotation.y);
    }
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
        return GetTranslationMatrix(position)   *
               GetYRotationMatrix  (rotation.y) *
               GetXRotationMatrix  (rotation.x) *
               GetZRotationMatrix  (rotation.z) *
               GetScaleMatrix      (scale);
    }
    
    // For normals.
    if (transformNormals)
    {
        return GetTransformMatrix(position, rotation, scale).Inv4().GetTransposed();
    }
    
    // For objects in world space.
    return GetScaleMatrix      (scale)      *
           GetZRotationMatrix  (rotation.z) *
           GetXRotationMatrix  (rotation.x) *
           GetYRotationMatrix  (rotation.y) *
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
