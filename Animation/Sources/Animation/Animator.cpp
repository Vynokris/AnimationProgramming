#include "Animation/Animator.h"

#include <iostream>

#include "Core/Engine.h"


// ----- Animation ----- //

Animation::Animation(const std::string& animName)
    : name(animName), keyframeCount((int)GetAnimKeyCount(name.c_str())-1) { }

void Animation::Update(const float& deltaTime)
{
    if (paused) return;
    keyframeTimer += deltaTime;

    if (keyframeTimer >= keyframeDuration)
    {
        keyframeTimer = 0;
        
        // Advance to the next keyframe when the current one is finished.
        if (!reverse)
        {
            curKeyframe++;
            if (curKeyframe == keyframeCount)
                curKeyframe = 0;
        }
        
        // If the animation is reversed, go back to the previous keyframe if the current one is finished.
        else
        {
            curKeyframe--;
            if (curKeyframe < 0)
                curKeyframe = keyframeCount-1;
        }
    }
}


// ----- Animator ----- //

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
        Animation* newAnim = new Animation(name);
        animations.insert(std::pair(name, newAnim));
        // allAnimations.emplace_back(newAnim);
    }
    return animations[name];
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
    }
    else
    {
        std::cout << "Unable to set " << name << " as current animation because it isn't in this animator.";
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
