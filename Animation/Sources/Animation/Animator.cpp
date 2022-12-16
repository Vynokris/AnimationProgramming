#include "Animation/Animator.h"
#include "Animation/Animation.h"
#include "Animation/Skeleton.h"
#include "Core/Engine.h"
#include <iostream>
using namespace Maths;


Animator::~Animator()
{
    for (const auto& [name, anim] : animations)
        delete anim;
}

Animation* Animator::AddAnimation(const std::string& name)
{
    // If the animation doesn't already exist, create it.
    if (animations.find(name) == animations.end())
    {
        Animation* newAnim = new Animation(name, skeleton);
        animations.insert(std::pair(name, newAnim));
    }
    return animations[name];
}

Animation* Animator::GetAnimation(const std::string& name)
{
    if (animations.find(name) != animations.end())
        return animations[name];
    return nullptr;
}

bool Animator::IsAnimating() const
{
    return !curAnimName.empty();
}

Animation* Animator::GetCurrentAnimation()
{
    if (!curAnimName.empty())
        return animations[curAnimName];
    return nullptr;
}

std::string Animator::GetCurrentAnimationName()
{
   return curAnimName;
}

void Animator::SetCurrentAnimation(const std::string& name)
{
    if (animations.find(name) != animations.end() || name.empty())
    {
        if (Animation* curAnim = GetCurrentAnimation())
        {
            curAnim->curKeyframe   = 0;
            curAnim->keyframeTimer = 0;
        }
        
        curAnimName = name;
        if (const Animation* curAnim = GetCurrentAnimation()) Log("Animator", "Switched to anim %s", curAnim->nameNoExtension.c_str());
        else                                                  Log("Animator", "Stopped animation");
    }
    else
    {
        Log("Animator", "WARNING! Unable to set %s as current animation because it isn't in this animator.", name.c_str());
    }
}

bool Animator::IsTransitioning() const
{
    return animTransition.IsRunning();
}

float Animator::GetTransitionCompletion() const
{
    return animTransition.GetCompletion();
}

Animation* Animator::GetTransitionAnimation()
{
    if (!animTransition.IsRunning()) return nullptr;

    return GetAnimation(animTransition.destAnimName);
}

std::string Animator::GetTransitionAnimationName()
{
    if (!animTransition.IsRunning()) return "";

    return animTransition.destAnimName;
}

void Animator::StartTransition(const std::string& destAnim, const float& duration)
{
    if (animTransition.IsRunning())
    {
        Log("Animator", "WARNING! Tried to start new transition but the current one isn't finished");
    }
    else if (!IsAnimating())
    {
        Log("Animator", "WARNING! Tried to start transition from default pose");
    }
    else
    {
        Log("Animator", "Started transition from %s into %s", curAnimName.c_str(), destAnim.c_str());
        animTransition.destAnimName = destAnim;
        animTransition.duration     = duration;
        animTransition.Reset();
        animTransition.Start();
    }
}

void Animator::Update(const float& deltaTime)
{
    // Update the current animation.
    if (IsAnimating()) GetAnimation(curAnimName)->Update(deltaTime);

    // Update the transition.
    animTransition.Update(deltaTime);

    // Update the skinning pose.
    skeleton.GetRootBone()->UpdateChildrenAnimatedTransform();
    skeleton.UpdateBoneMatrices();
    SetSkinningPose(skeleton.GetBoneMatrices()[0].AsPtr(), skeleton.GetBoneMatrices().size());
}
