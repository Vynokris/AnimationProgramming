#pragma once
#include "Maths/Transform.h"
#include <string>
#include <vector>
class Skeleton;


class Animation
{
private:
    // Stores the local transforms for each keyframe of each bone.
    // Rows: boneIDs
    // Columns: keyframes
    std::vector<std::vector<Maths::Transform>> localBoneTransforms;

    // Stores interpolated transform for each bone.
    // Updated by skeleton.UpdateAnimation();
    std::vector<Maths::Transform> smoothTransforms;
    
public:
    const std::string name;
    const std::string nameNoExtension;
    const size_t      keyframeCount;
    
    float  keyframeDuration = 1/30.f;
    size_t curKeyframe      = 0;
    size_t prevKeyframe     = 0;
    float  keyframeTimer    = 0;
    bool   reverse          = false;
    bool   paused           = false;
    
    Animation(const std::string& animName, const Skeleton& skeleton);
    void Update(const float& deltaTime);

    const Maths::Transform& GetLocalBoneTransform(const size_t& boneId, const size_t& keyframe) const;
    Maths::Transform& GetSmoothTransform(const size_t& boneId);
};

