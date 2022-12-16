#include "Animation/Animator.h"
#include "Animation/Animation.h"
#include "Core/Engine.h"

#include <iostream>


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

bool Animator::IsAnimating() const
{
    return !currentAnimation.empty();
}

Animation* Animator::GetAnimation(const std::string& name)
{
    if (animations.find(name) != animations.end())
        return animations[name];
    return nullptr;
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
        
        currentAnimation = name;
        if (const Animation* curAnim = GetCurrentAnimation()) Log("Animator", "Switched to anim %s", curAnim->nameNoExtension.c_str());
        else                                                  Log("Animator", "Stopped animation");
    }
    else
    {
        Log("Animator", "WARNING! Unable to set %s as current animation because it isn't in this animator.", name.c_str());
    }
}

void Animator::UpdateCurrentAnimation(const float& deltaTime)
{
    if (Animation* curAnim = GetAnimation(currentAnimation))
        curAnim->Update(deltaTime);
}

Animation* Animator::GetCurrentAnimation()
{
    if (!currentAnimation.empty())
        return animations[currentAnimation];
    return nullptr;
}
