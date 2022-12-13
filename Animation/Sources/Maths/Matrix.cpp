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

    // TODO: Fix this shit lmao.
    // For objects in world space.
    return GetZRotationMatrix(rotation.z) *
           GetXRotationMatrix(-rotation.x) *
           GetYRotationMatrix(rotation.y);
    /*
    const float cX = cos(rotation.x), sX = sin(rotation.x);
    const float cY = cos(rotation.y), sY = sin(rotation.y);
    const float cZ = cos(rotation.z), sZ = sin(rotation.z);
    return Mat4(cX*cY*cZ-sX*sZ, -sX*cY*cZ-cX*sZ, sY*cZ, 0,
                cX*cY*sZ+sX*cZ, -sX*cY*sZ+cX*cZ, sY*sZ, 0,
                -cX*sY,         sX*sY,           cY,    0,
                0,              0,               0,     1);
    */
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
