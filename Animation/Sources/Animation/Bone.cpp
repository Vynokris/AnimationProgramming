#include "Animation/Bone.h"
#include "Animation/Animation.h"
#include "Animation/Animator.h"
#include "Core/Engine.h"
using namespace Maths;

Bone::Bone(const size_t& boneIndex, const std::string& boneName, Animator& skeletonAnimator)
	: animator(skeletonAnimator), index(boneIndex), name(boneName) {}

void Bone::SetChildrenDefaultTransform(const Mat4 & parentMat)
{
	// Get the default transform.
	Vector3 position; Quaternion rotation;
	GetSkeletonBoneLocalBindTransform(index, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
	defaultTransform.SetPosRot(position, rotation);
	
	// Get the world matrix and update children.
	const Mat4 curMat = defaultTransform.GetLocalMat() * parentMat;
	for (Bone* child : children)
	{
		child->defaultTransform.SetParentMat(curMat);
		child->SetChildrenDefaultTransform(curMat);
	}
}

void Bone::UpdateChildrenAnimation(Animation* anim, const Mat4& parentMat) const
{
	if (!anim) return;
	
	// Get current and previous pose local transforms.
	const Transform& curPoseTransform  = anim->GetLocalBoneTransform(index, anim->curKeyframe);
	const Transform& prevPoseTransform = anim->GetLocalBoneTransform(index, anim->prevKeyframe);

	// Interpolate between the current and previous transform.
    const float      lerpVal      = anim->keyframeTimer / anim->keyframeDuration;
	const Vector3    animPosition = Vector3   ::Lerp (prevPoseTransform.GetPosition(), curPoseTransform.GetPosition(), lerpVal);
	const Quaternion animRotation = Quaternion::SLerp(prevPoseTransform.GetRotation(), curPoseTransform.GetRotation(), lerpVal);
	anim->GetSmoothTransform(index).SetPosRot(animPosition, animRotation);

	// Get the world matrix and update children.
	const Mat4 curMat = anim->GetSmoothTransform(index).GetLocalMat() * defaultTransform.GetLocalMat() * parentMat;
	for (const Bone* child : children)
	{
		anim->GetSmoothTransform(child->index).SetParentMat(curMat);
		child->UpdateChildrenAnimation(anim, curMat);
	}
}

/*
Mat4 Bone::GetLocalMat() const
{
	if (!animator.IsAnimating())
		return defaultTransform.GetLocalMat();
	
	// Apply the animation transform to the default transform.
	return animTransform.GetLocalMat() * defaultTransform.GetLocalMat();
}

Mat4 Bone::GetParentMat() const
{
	return animator.IsAnimating() ? animTransform.GetParentMat() : defaultTransform.GetParentMat();
}
*/
