#include "Maths.h"

Mat4 Maths::getTranslationMatrix(const Vector3& translation)
{
    return Mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -translation.x, translation.y, translation.z, 1);
}

Mat4 Maths::getScaleMatrix(const Vector3& scale)
{
    return Mat4(scale.x, 0, 0, 0,
                0, scale.y, 0, 0,
                0, 0, scale.z, 0,
                0, 0, 0, 1);
}

Mat4 Maths::getXRotationMatrix(const float& angle)
{
    return Mat4(1, 0, 0, 0,
                0, cosf(angle), -sinf(angle), 0,
                0, sinf(angle), cosf(angle), 0,
                0, 0, 0, 1);
}

Mat4 Maths::getYRotationMatrix(const float& angle)
{
    return Mat4(cosf(angle), 0, sinf(angle), 0,
                0, 1, 0, 0,
                -sinf(angle), 0, cosf(angle), 0,
                0, 0, 0, 1);
}

Mat4 Maths::getZRotationMatrix(const float& angle)
{
    return Mat4(cosf(angle), -sinf(angle), 0, 0,
                sinf(angle), cosf(angle), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

Mat4 Maths::getRotationMatrix(const Vector3& rotation, const bool& reverse)
{
    // For cameras.
    if (reverse)
    {
        return getYRotationMatrix(rotation.y) *
               getXRotationMatrix(-rotation.x) *
               getZRotationMatrix(rotation.z);
    }
    // For objects in world space.
    else
    {
        return getZRotationMatrix(rotation.z) *
               getXRotationMatrix(-rotation.x) *
               getYRotationMatrix(rotation.y);
    }
}

Mat4 Maths::getTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse, const bool& transformNormals)
{
    // For cameras.
    if (reverse)
    {
        return getTranslationMatrix(position)   *
               getYRotationMatrix  (rotation.y) *
               getXRotationMatrix  (rotation.x) *
               getZRotationMatrix  (rotation.z) *
               getScaleMatrix      (scale);
    }
    // For normals.
    else if (transformNormals)
    {
        return getTransformMatrix(position, rotation, scale).inv4().transpose();
    }
    // For objects in world space.
    else
    {
        return getScaleMatrix      (scale)      *
               getZRotationMatrix  (rotation.z) *
               getXRotationMatrix  (rotation.x) *
               getYRotationMatrix  (rotation.y) *
               getTranslationMatrix(position);
    }
}