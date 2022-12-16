#pragma once
#include <string>
class Animator;
class Animation;

class AnimTransition
{
private:
    Animator& animator;
    
    Animation* curAnim  = nullptr;
    Animation* destAnim = nullptr;

    float curAnimDurationOrig  = 0;
    float destAnimDurationOrig = 0;
    float curAnimKeyframeDurationOrig  = 0;
    float destAnimKeyframeDurationOrig = 0;
    
public:
    std::string destAnimName;
    bool  syncAnims = true;
    float duration  =  1.f;
    float timer     = -1.f;

    AnimTransition(Animator& skeletonAnimator) : animator(skeletonAnimator) {}
    bool  IsRunning    () const { return timer >= 0 && !IsFinished(); }
    bool  IsFinished   () const { return timer >= duration; }
    float GetCompletion() const;
    void Start();
    void Reset();
    void Update(const float& deltaTime);
};
