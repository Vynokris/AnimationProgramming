#include "Maths/Maths.h"
using namespace Maths;


// ----- Constructors ----- //
Transform::Transform(const bool& _isCamera)
    : pos(), rot(), scale(1), worldMat(true), isCamera(_isCamera)
{
    UpdateLocalMat();
}

Transform::Transform(const Vector3& _pos, const Quaternion& _rot, const Vector3& _scale, const bool& _isCamera)
    : pos(_pos), rot(_rot), scale(_scale), worldMat(true), isCamera(_isCamera)
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

// ----- Matrices ----- //
void Transform::UpdateLocalMat() 
{
    if (!isCamera) localMat = GetTransformMatrix( pos, rot, scale);
    else           localMat = GetTransformMatrix(-pos, rot, { 1, 1, 1 }, true);
}
