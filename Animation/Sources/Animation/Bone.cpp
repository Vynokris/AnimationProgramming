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

void Bone::UpdateChildrenAnimatedTransform(const Mat4& parentMat)
{
	if (!animator.IsAnimating()) return;
	
	// During a transition, use the animated local bone transform interpolated between the current and destination animations.
	if (animator.IsTransitioning())
	{
		const Transform curAnimatedTransform  = animator.GetCurrentAnimation()   ->GetAnimatedLocalBoneTransform(index);
		const Transform destAnimatedTransform = animator.GetTransitionAnimation()->GetAnimatedLocalBoneTransform(index);
		const Transform lerpTransform         = Transform::Lerp(curAnimatedTransform, destAnimatedTransform, animator.GetTransitionCompletion());
		animatedTransform.SetPosRot(lerpTransform.GetPosition(), lerpTransform.GetRotation());
	}
	
	// During an animation, use current animated local bone transform.
	else
	{
		const Transform curAnimatedTransform = animator.GetCurrentAnimation()->GetAnimatedLocalBoneTransform(index);
		animatedTransform.SetPosRot(curAnimatedTransform.GetPosition(), curAnimatedTransform.GetRotation());
	}
	
	// Get the world matrix and update children.
	const Mat4 curMat = animatedTransform.GetLocalMat() * defaultTransform.GetLocalMat() * parentMat;
	for (Bone* child : children)
	{
		child->animatedTransform.SetParentMat(curMat);
		child->UpdateChildrenAnimatedTransform(curMat);
	}
}
