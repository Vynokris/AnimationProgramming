#include "Animation/AnimTransition.h"

#include "Animation/Animation.h"
#include "Animation/Animator.h"

float AnimTransition::GetCompletion() const
{
    if (!IsRunning()) return 0;
    if (IsFinished()) return 1;
    return timer / duration;
}

void AnimTransition::Start()
{
    timer = 0;
    
    curAnim  = animator.GetCurrentAnimation();
    destAnim = animator.GetAnimation(destAnimName);
    
    if (syncAnims)
        destAnim->SetCompletion(curAnim->GetCompletion());
}

void AnimTransition::Reset()
{
    timer    = -1;
    curAnim  = nullptr;
    destAnim = nullptr;
}

void AnimTransition::Update(const float& deltaTime)
{
    if (IsRunning())
    {
        timer += deltaTime;
        
        if (IsFinished())
        {
            curAnim  = nullptr;
            destAnim = nullptr;
            animator.SetCurrentAnimation(destAnimName);
            return;
        }
        
        if (destAnim)
        {
            destAnim->Update(deltaTime);
        }
    }
}
