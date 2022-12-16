#include "Animation/AnimTransition.h"

#include "Animation/Animation.h"
#include "Animation/Animator.h"
#include "Core/Engine.h"

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

    // Get default animation durations and keyframe durations.
    if (curAnim)
    {
        curAnimDurationOrig         = curAnim->GetDuration();
        curAnimKeyframeDurationOrig = curAnim->keyframeDuration;
    }
    if (destAnim)
    {
        destAnimDurationOrig         = destAnim->GetDuration();
        destAnimKeyframeDurationOrig = destAnim->keyframeDuration;
    }

    // Synchronize the destination anim completion with the current anim completion.
    if (syncAnims) destAnim->SetCompletion(curAnim->GetCompletion());
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
            // Reset animation speeds and update the current animation.
            if (curAnim ) curAnim ->keyframeDuration = curAnimKeyframeDurationOrig;
            if (destAnim) destAnim->keyframeDuration = destAnimKeyframeDurationOrig;
            curAnim  = nullptr;
            destAnim = nullptr;
            animator.SetCurrentAnimation(destAnimName);
            return;
        }

        if (syncAnims && curAnim && destAnim)
        {
            // Interpolate the start and destination animation speeds to synchronize them.
            const float interpolatedDuration = Maths::lerp(curAnimDurationOrig, destAnimDurationOrig, GetCompletion());
            const float curDurationRatio  = interpolatedDuration / curAnimDurationOrig;
            const float destDurationRatio = interpolatedDuration / destAnimDurationOrig;
            curAnim ->keyframeDuration = curDurationRatio  * curAnimKeyframeDurationOrig;
            destAnim->keyframeDuration = destDurationRatio * destAnimKeyframeDurationOrig;
        }
        
        if (destAnim)
        {
            destAnim->Update(deltaTime);
        }
    }
}
