#pragma once
#include "Maths/Transform.h"
#include <string>
#include <vector>
class Skeleton;

constexpr float DEFAULT_KEYFRAME_DURATION = 1; // 1/30.f;


class Animation
{
private:
    Skeleton& skeleton;
    
    // Stores the local transforms for each keyframe of each bone.
    // Rows: boneIDs
    // Columns: keyframes
    std::vector<std::vector<Maths::Transform>> localBoneTransforms;

    // Stores smoothly animated local transform for each bone.
    std::vector<Maths::Transform> animatedLocalTransforms;
    
public:
    const std::string name;
    const std::string nameNoExtension;
    const size_t      keyframeCount;
    
    float  keyframeDuration = DEFAULT_KEYFRAME_DURATION;
    size_t curKeyframe      = 0;
    size_t prevKeyframe     = 0;
    float  keyframeTimer    = 0;
    bool   reverse          = false;
    bool   paused           = false;
    
    Animation(const std::string& animName, Skeleton& baseSkeleton);
    void Update(const float& deltaTime);

    float GetDuration  () const;
    float GetCompletion() const;
    void  SetCompletion(const float& completion);

    Maths::Transform GetAnimatedLocalBoneTransform(const size_t& boneId) const;

private:
    void UpdateAnimatedLocalBoneTransforms();
};

