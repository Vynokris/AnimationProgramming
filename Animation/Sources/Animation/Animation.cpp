#include "Animation/Animation.h"
#include "Animation/Skeleton.h"
#include "Core/Engine.h"
using namespace Maths;


Animation::Animation(const std::string& animName, Skeleton& baseSkeleton)
    : skeleton(baseSkeleton),
      name(animName),
      nameNoExtension(animName.substr(0, animName.size()-5)),
      keyframeCount(GetAnimKeyCount(name.c_str()))
{
    const size_t boneCount = skeleton.GetBoneCount();
    localBoneTransforms    .resize(boneCount);
    animatedLocalTransforms.resize(boneCount);

    for (size_t boneId = 0; boneId < boneCount; ++boneId)
    {
        localBoneTransforms[boneId].resize(keyframeCount);

        for (size_t keyframe = 0; keyframe < keyframeCount; ++keyframe)
        {
            Vector3 position; Quaternion rotation;
            GetAnimLocalBoneTransform(name.c_str(), boneId, keyframe, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
            localBoneTransforms[boneId][keyframe].SetPosRot(position, rotation);
        }
    }
}

void Animation::Update(const float& deltaTime)
{
    // Note: All animations skip keyframe 0 when looping 
    //       because it is assumed to be the same as the last keyframe.

    if (paused) return;
    keyframeTimer += deltaTime;

    // Change keyframe when the keyframe timer is finished.
    if (keyframeTimer >= keyframeDuration)
    {
        keyframeTimer = 0;
        prevKeyframe = curKeyframe;
        if (!reverse) {
            curKeyframe++;
            if (curKeyframe >= keyframeCount)
                curKeyframe = 1;
        }
        else {
            curKeyframe--;
            if (curKeyframe <= 0)
                curKeyframe = keyframeCount-1;
        }
    }

    UpdateAnimatedLocalBoneTransforms();
}

float Animation::GetDuration() const
{
    return (float)keyframeCount * keyframeDuration;
}

float Animation::GetCompletion() const
{
    return ((float)curKeyframe * keyframeDuration + keyframeTimer) / GetDuration();
}

void Animation::SetCompletion(const float& completion)
{
    const float curTime = completion * ((float)keyframeCount * keyframeDuration);
    curKeyframe   = (size_t)floorInt(curTime / keyframeDuration);
    keyframeTimer = fmodf(curTime, keyframeDuration);
    prevKeyframe  = curKeyframe + (reverse ? -1 : 1);
    if (prevKeyframe >= keyframeCount)
        prevKeyframe = 1;
    if (prevKeyframe <= 0)
        prevKeyframe = keyframeCount-1;

    UpdateAnimatedLocalBoneTransforms();
}

Transform Animation::GetAnimatedLocalBoneTransform(const size_t& boneId) const
{
    if (boneId > animatedLocalTransforms.size()) return Transform();
    return animatedLocalTransforms[boneId];
}

void Animation::UpdateAnimatedLocalBoneTransforms()
{
    // Update each bone's animated local transform.
    for (const Bone* bone : skeleton.GetBones())
    {
        const Transform& prevPoseTransform = localBoneTransforms[bone->index][prevKeyframe];
        const Transform& curPoseTransform  = localBoneTransforms[bone->index][curKeyframe];
        const float      lerpVal      = keyframeTimer / keyframeDuration;
        const Vector3    animPosition = Vector3   ::Lerp (prevPoseTransform.GetPosition(), curPoseTransform.GetPosition(), lerpVal);
        const Quaternion animRotation = Quaternion::SLerp(prevPoseTransform.GetRotation(), curPoseTransform.GetRotation(), lerpVal);
        animatedLocalTransforms[bone->index] = Transform(animPosition, animRotation, {1});
    }
}