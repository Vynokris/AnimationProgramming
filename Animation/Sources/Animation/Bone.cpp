#include "Animation/Bone.h"
#include <Core/Engine.h>

Bone::Bone(const int& _index, const std::string& _name, const Transform& _defaultTransform)
	: index(_index), name(_name), defaultTransform(_defaultTransform), animation(index) {}

void Bone::SetChildrenDefaultTransform(const Mat4 & parentMat)
{
	Vector3 position; Quaternion rotation;
	GetSkeletonBoneLocalBindTransform(index, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);
	defaultTransform.SetPosRot(position, rotation);
	
	const Mat4 curMat = defaultTransform.GetLocalMat() * parentMat;
	for (Bone* child : children)
	{
		child->defaultTransform.SetParentMat(curMat);
		child->SetChildrenDefaultTransform(curMat);
	}
}

void Bone::UpdateChildrenAnimation(const float& deltaTime, const Mat4& parentMat)
{
	animation.UpdateTimer(deltaTime);
	animation.UpdatePoseTransform();

	const Mat4 curMat = GetLocalMat() * parentMat;
	for (Bone* child : children)
	{
		child->animation.SetParentMat(curMat);
		child->UpdateChildrenAnimation(deltaTime, curMat);
	}
}

Mat4 Bone::GetLocalMat() const
{
	// Apply the animation transform to the default transform.
	return animation.GetPoseLocalMat() * defaultTransform.GetLocalMat();
}

Mat4 Bone::GetWorldMat() const
{
	// Apply the parent transforms to the default transform.
	return GetLocalMat() * animation.GetParentMat();
}
