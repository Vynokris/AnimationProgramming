#include "Animation/Animation.h"

#include "Core/Engine.h"

void Animation::SetCurrentAnimation(const char* animName, const int& boneIndex)
{
    curAnimName = animName;
    
    Vector3 position; Quaternion rotation;
    GetAnimLocalBoneTransform(animName, boneIndex, (int)(GetAnimKeyCount(animName))-2, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform.SetPosition(position); prevPoseTransform.SetRotation(rotation);
    curKeyFrame = 0;
    keyFrameTimer = KEYFRAME_DURATION;
}

void Animation::UpdateTimer(const float& deltaTime)
{
    keyFrameTimer += deltaTime;
}

void Animation::UpdatePoseTransform(const int& boneIndex)
{
    if (keyFrameTimer < KEYFRAME_DURATION) return;
    
    keyFrameTimer = 0;
    curKeyFrame   = (curKeyFrame + 1) % ((int)GetAnimKeyCount(curAnimName)-1);
    
    Vector3 position; Quaternion rotation;
    GetAnimLocalBoneTransform(curAnimName, boneIndex, curKeyFrame, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform = poseTransform;
    poseTransform.SetPosition(position); poseTransform.SetRotation(rotation);
}

Mat4 Animation::GetPoseMat() const
{
    const float lerpVal = keyFrameTimer / KEYFRAME_DURATION;
    
    Transform smoothTransform;
    smoothTransform.SetPosition(Point3Lerp(lerpVal, prevPoseTransform.GetPosition(), poseTransform.GetPosition()));
    smoothTransform.SetRotation(Quaternion::NLerp(prevPoseTransform.GetRotation(), poseTransform.GetRotation(), lerpVal));
    return smoothTransform.GetLocalMat();
}
