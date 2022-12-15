#include "Animation/BoneAnim.h"

#include "Animation/Animator.h"
#include "Core/Engine.h"


void BoneAnim::UpdatePoseTransform()
{
    const Animation* curAnim = animator.GetCurrentAnimation();
    if (!curAnim || curKeyframe == curAnim->curKeyframe) return;

    // Advance to the next keyframe.
    curKeyframe = curAnim->curKeyframe;

    // Get the new keyframe transform.
    Vector3 position; Quaternion rotation;
    GetAnimLocalBoneTransform(curAnim->name.c_str(), boneIndex, curKeyframe, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
    prevPoseTransform = poseTransform;
    poseTransform.SetPosRot(position, rotation);
}

Mat4 BoneAnim::GetPoseLocalMat() const
{
    const Animation* curAnim = animator.GetCurrentAnimation();
    if (!curAnim) return Mat4();
    
    // Interpolate between the previous transform and the next.
    const float lerpVal = curAnim->keyframeTimer / curAnim->keyframeDuration;
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
