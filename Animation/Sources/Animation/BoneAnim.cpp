#include "Animation/BoneAnim.h"

#include "Core/Engine.h"

void BoneAnim::SetCurrentAnimation(const char* animName)
{
    curAnimName = animName;
    Vector3 position; Quaternion rotation;

    // Set the previous pose to the last keyframe.
    GetAnimLocalBoneTransform(animName, boneIndex, 0, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform.SetPosRot(position, rotation);

    // Set the current pose to the first keyframe.
    GetAnimLocalBoneTransform(animName, boneIndex, 1, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    poseTransform.SetPosRot(position, rotation);

    // Initialize the current keyframe and the keyframe timer.
    curKeyFrame   = 1;
    keyFrameTimer = 0;
}

void BoneAnim::UpdateTimer(const float& deltaTime)
{
    keyFrameTimer += deltaTime;
}

void BoneAnim::UpdatePoseTransform()
{
    if (keyFrameTimer < KEYFRAME_DURATION) return;

    // Advance to the next keyframe.
    keyFrameTimer = 0;
    curKeyFrame   = (curKeyFrame + 1) % (int)GetAnimKeyCount(curAnimName);
    if (curKeyFrame == 0) curKeyFrame++;

    // Get the new keyframe transform.
    Vector3 position; Quaternion rotation;
    GetAnimLocalBoneTransform(curAnimName, boneIndex, curKeyFrame, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform = poseTransform;
    poseTransform.SetPosRot(position, rotation);
}

Mat4 BoneAnim::GetPoseLocalMat() const
{
    const float lerpVal = keyFrameTimer / KEYFRAME_DURATION;

    // Interpolate between the previous transform and the next.
    const Transform smoothTransform =
    {
        Point3Lerp       (prevPoseTransform.GetPosition(), poseTransform.GetPosition(), lerpVal),
        Quaternion::SLerp(prevPoseTransform.GetRotation(), poseTransform.GetRotation(), lerpVal),
        Vector3(1)
    };
    return smoothTransform.GetLocalMat();
}

Mat4 BoneAnim::GetParentMat() const
{
    return poseTransform.GetParentMat();
}

void BoneAnim::SetParentMat(const Mat4& worldMat)
{
    poseTransform.SetParentMat(worldMat);
}
