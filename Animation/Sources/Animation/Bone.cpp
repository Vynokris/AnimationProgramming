#include "Animation/Bone.h"
#include <Core/Engine.h>

#include "Animation/Animation.h"
#include "Animation/Animator.h"

Bone::Bone(const int& boneIndex, const std::string& boneName, Animator& skeletonAnimator)
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

void Bone::UpdateChildrenAnimation(const float& deltaTime, const Mat4& parentMat)
{
	// Get current and previous pose local transforms.
	const Animation* curAnim = animator.GetCurrentAnimation(); if (!curAnim) return;
	const Transform& curPoseTransform  = curAnim->GetLocalBoneTransform(index, curAnim->curKeyframe);
	const Transform& prevPoseTransform = curAnim->GetLocalBoneTransform(index, curAnim->prevKeyframe);

	// Interpolate between the current and previous transform.
    const float      lerpVal      = curAnim->keyframeTimer / curAnim->keyframeDuration;
	const Vector3    animPosition = Point3Lerp       (prevPoseTransform.GetPosition(), curPoseTransform.GetPosition(), lerpVal);
	const Quaternion animRotation = Quaternion::SLerp(prevPoseTransform.GetRotation(), curPoseTransform.GetRotation(), lerpVal);
	animTransform.SetPosRot(animPosition, animRotation);

	// Get the world matrix and update children.
	const Mat4 curMat = GetLocalMat() * parentMat;
	for (Bone* child : children)
	{
		child->animTransform.SetParentMat(curMat);
		child->UpdateChildrenAnimation(deltaTime, curMat);
	}
}

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
