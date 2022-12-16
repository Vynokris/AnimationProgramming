#include "Animation/Animation.h"
#include "Animation/Skeleton.h"
#include "Core/Engine.h"
using namespace Maths;


Animation::Animation(const std::string& animName, const Skeleton& skeleton)
    : name(animName),
      nameNoExtension(animName.substr(0, animName.size()-5)),
      keyframeCount(GetAnimKeyCount(name.c_str()))
{
    const size_t boneCount = skeleton.GetBoneCount();
    localBoneTransforms.resize(boneCount);
    smoothTransforms   .resize(boneCount);

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
    if (paused) return;
    keyframeTimer += deltaTime;

    // Note: All animations skip keyframe 0 when looping 
    //       because it is assumed to be the same as the last keyframe.

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
}

const Transform& Animation::GetLocalBoneTransform(const size_t& boneId, const size_t& keyframe) const
{
    assert(boneId < localBoneTransforms.size() && keyframe < localBoneTransforms[boneId].size());
    return localBoneTransforms[boneId][keyframe];
}

Transform& Animation::GetSmoothTransform(const size_t& boneId)
{
    assert(boneId < smoothTransforms.size());
    return smoothTransforms[boneId];
}
