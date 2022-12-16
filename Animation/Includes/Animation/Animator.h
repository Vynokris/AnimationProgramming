#pragma once
#include <string>
#include <unordered_map>
class Animation;
class Skeleton;

constexpr const char* WALK_ANIMATION = "ThirdPersonWalk.anim";
constexpr const char* RUN_ANIMATION  = "ThirdPersonRun.anim";

class Animator
{
private:
    const Skeleton& skeleton;
    std::unordered_map<std::string, Animation*> animations;
    std::string currentAnimation;
    
public:
    Animator(const Skeleton& baseSkeleton) : skeleton(baseSkeleton) {}
    ~Animator();
    
    std::unordered_map<std::string, Animation*>& GetAllAnimations() { return animations; }
    Animation* GetAnimation(const std::string& name);
    Animation* AddAnimation(const std::string& name);

    bool       IsAnimating() const;
    Animation* GetCurrentAnimation();
    void       SetCurrentAnimation(const std::string& name);
    void       UpdateCurrentAnimation(const float& deltaTime);
};
