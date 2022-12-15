#pragma once
#include <string>
#include <unordered_map>

class Animation
{
public:
    const std::string name;
    const std::string nameNoExtension;
    const int         keyframeCount;
    
    float keyframeDuration = 1/30.f;
    int   curKeyframe      = 0;
    float keyframeTimer    = 0;
    bool  reverse          = false;
    bool  paused           = false;
    
    Animation(const std::string& animName);
    void Update(const float& deltaTime);
};

class Animator
{
private:
    std::unordered_map<std::string, Animation*> animations;
    std::string currentAnimation;
    
public:
    ~Animator();
    
    std::unordered_map<std::string, Animation*>& GetAllAnimations() { return animations; }
    Animation* GetAnimation(const std::string& name);
    Animation* AddAnimation(const std::string& name);

    Animation* GetCurrentAnimation();
    void SetCurrentAnimation(const std::string& name);
    void UpdateCurrentAnimation(const float& deltaTime);
};
