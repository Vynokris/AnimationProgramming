#include "Maths/Maths.h"
using namespace Maths;


// ----- Constructors ----- //
Transform::Transform(const bool& _isCamera)
    : scale(1), isCamera(_isCamera)
{
    UpdateLocalMat();
}

Transform::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& _scale, const bool& _isCamera)
    : pos(position), rot(rotation), scale(_scale), isCamera(_isCamera)
{
    UpdateLocalMat();
}

// ----- Position ----- //
Vector3 Transform::GetPosition() const { return pos; }
void    Transform::SetPosition(const Vector3& position) { pos  = position; UpdateLocalMat(); }
void    Transform::Move       (const Vector3& movement) { pos += movement; UpdateLocalMat(); }

// ----- Forward ----- //
Vector3 Transform::Forward() const                    { return rot.ToAngleAxis().axis; }
Vector3 Transform::Up()      const                    { return Vector3(0); } // TODO: fix this.
Vector3 Transform::Right()   const                    { return Vector3(0); } // TODO: fix this.
void    Transform::SetForward(const Vector3& forward) { UpdateLocalMat(); }     // TODO: fix this.

// ----- Rotation ----- //
Quaternion Transform::GetRotation() const                     { return rot; }
void       Transform::SetRotation(const Quaternion& rotation) { rot = rotation; UpdateLocalMat(); }
void       Transform::Rotate     (const Quaternion& rotation) 
{
    rot = rotation.RotateQuat(rot);
    UpdateLocalMat(); 
}

// ----- Scale ----- //
Vector3 Transform::GetScale()        const         { return scale;   }
Vector3 Transform::GetUniformScale() const         { return std::max(scale.x, std::max(scale.y, scale.z)); }
void    Transform::SetScale(const Vector3& _scale) { scale = _scale; UpdateLocalMat(); }

// ----- Is Camera ----- //
bool Transform::IsCamera() const                   { return isCamera; }
void Transform::SetIsCamera(const bool& _isCamera) { isCamera = _isCamera; UpdateLocalMat(); }

// ----- Multiple Values ----- //
void Transform::SetPosRot(const Vector3& position, const Quaternion& rotation)                        { pos = position; rot = rotation; UpdateLocalMat(); }
void Transform::SetValues(const Vector3& position, const Quaternion& rotation, const Vector3& _scale) { pos = position; rot = rotation; scale = _scale; UpdateLocalMat(); }

// ----- Interpolation ----- //
Transform Transform::Lerp(const Transform& start, const Transform& dest, const float& val, const bool& useSlerp)
{
    const Vector3    lerpPos   = Vector3::Lerp(start.GetPosition(), dest.GetPosition(), val);
    const Quaternion lerpRot   = useSlerp ? Quaternion::SLerp(start.GetRotation(), dest.GetRotation(), val)
                                          : Quaternion::NLerp(start.GetRotation(), dest.GetRotation(), val);
    const Vector3    lerpScale = Vector3::Lerp(start.GetScale(), dest.GetScale(), val);
    return Transform(lerpPos, lerpRot, lerpScale);
}

// ----- Matrices ----- //
void Transform::UpdateLocalMat() 
{
    if (!isCamera) localMat = Mat4::FromTransform( pos, rot, scale);
    else           localMat = Mat4::FromTransform(-pos, rot, { 1, 1, 1 }, true);
}
