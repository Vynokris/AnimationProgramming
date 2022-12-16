#pragma once
#include <string>
#include <unordered_map>
#include "AnimTransition.h"

namespace Maths
{
    class Transform;
}
class Animation;
class Skeleton;

constexpr const char* WALK_ANIMATION = "ThirdPersonWalk.anim";
constexpr const char* RUN_ANIMATION  = "ThirdPersonRun.anim";


class Animator
{
private:
    Skeleton&      skeleton;
    std::string    curAnimName;
    AnimTransition animTransition;
    std::unordered_map<std::string, Animation*> animations;
    
public:
    Animator(Skeleton& baseSkeleton) : skeleton(baseSkeleton), animTransition(*this) {}
    ~Animator();
    
    Animation* AddAnimation(const std::string& name);
    Animation* GetAnimation(const std::string& name);
    std::unordered_map<std::string, Animation*>& GetAllAnimations() { return animations; }

    bool        IsAnimating            () const;
    Animation*  GetCurrentAnimation    ();
    std::string GetCurrentAnimationName();
    void        SetCurrentAnimation(const std::string& name);

    bool        IsTransitioning           () const;
    float       GetTransitionCompletion   () const;
    Animation*  GetTransitionAnimation    ();
    std::string GetTransitionAnimationName();
    void        StartTransition(const std::string& destAnim, const float& duration = 1.f);
    
    void Update(const float& deltaTime);
};
