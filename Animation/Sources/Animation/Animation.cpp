#include "Animation/Animation.h"

#include "Core/Engine.h"

void Animation::SetCurrentAnimation(const char* animName)
{
    curAnimName = animName;
    Vector3 position; Quaternion rotation;

    // Set the previous pose to the last keyframe.
    GetAnimLocalBoneTransform(animName, boneIndex, (int)(GetAnimKeyCount(animName))-1, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform.SetPosition(position); prevPoseTransform.SetRotation(rotation);

    // Set the current pose to the first keyframe.
    GetAnimLocalBoneTransform(animName, boneIndex, 0, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    poseTransform.SetPosition(position); poseTransform.SetRotation(rotation);

    // Initialize the current keyframe and the keyframe timer.
    curKeyFrame = 0;
    keyFrameTimer = 0;
}

void Animation::UpdateTimer(const float& deltaTime)
{
    keyFrameTimer += deltaTime;
}

void Animation::UpdatePoseTransform()
{
    if (keyFrameTimer < KEYFRAME_DURATION) return;
    
    keyFrameTimer = 0;
    curKeyFrame   = (curKeyFrame + 1) % (int)GetAnimKeyCount(curAnimName);
    
    Vector3 position; Quaternion rotation;
    GetAnimLocalBoneTransform(curAnimName, boneIndex, curKeyFrame, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform = poseTransform;
    poseTransform.SetPosition(position); poseTransform.SetRotation(rotation);
}

Mat4 Animation::GetPoseMat() const
{
    const float lerpVal = keyFrameTimer / KEYFRAME_DURATION;
    
    const Transform smoothTransform =
    {
        Point3Lerp       (prevPoseTransform.GetPosition(), poseTransform.GetPosition(), lerpVal),
        Quaternion::SLerp(prevPoseTransform.GetRotation(), poseTransform.GetRotation(), lerpVal),
        Vector3(1)
    };
    return smoothTransform.GetLocalMat();
}
