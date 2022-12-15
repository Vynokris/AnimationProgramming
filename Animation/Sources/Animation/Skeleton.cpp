#include "Animation/Skeleton.h"

#include <iostream>
#include <algorithm>

#include "Core/Engine.h"

Skeleton:: Skeleton() : rootBone(nullptr), bones({}) { }
Skeleton::~Skeleton()
{
	for (const Bone* bone : bones)
		delete bone;
	bones.clear();
}

void Skeleton::SetRootBone(Bone* bone)
{
	rootBone = bone;
}

Bone* Skeleton::GetRootBone() const
{
	return rootBone;
}

void Skeleton::AddBone(Bone* bone)
{
	if (!DoesBoneExist(bone))
	{
		bones.push_back(bone);
		Log("Skeleton", "Added bone %s (id: %d)", bone->name.c_str(), bone->index);
	}
}

void Skeleton::RemoveBone(const int& id)
{
	Bone* bone = GetBone(id);
	if (!DoesBoneExist(bone)) return;

	Log("Skeleton", "Removed bone %s (id: %d)", bone->name.c_str(), bone->index);
	bones.erase(std::remove(bones.begin(), bones.end(), bone), bones.end());

	delete bone;
}

bool Skeleton::DoesBoneExist(const Bone* bone)
{
	return std::find(bones.begin(), bones.end(), bone) != bones.end();
}

void Skeleton::UpdateAnimation(const float& deltaTime)
{
	animator.UpdateCurrentAnimation(deltaTime);
	GetRootBone()->UpdateChildrenAnimation(deltaTime);
	UpdateBoneMatrices();
	
	SetSkinningPose(GetBoneMatrices()[0].AsPtr(), GetBoneMatrices().size());
}

void Skeleton::Draw(const Vector3& offset) const
{
	for (int boneId = 0; boneId < (int)bones.size(); boneId++)
	{
		// Stop if the bone is the root or the pelvis.
		if (!bones[boneId]->parent || !bones[boneId]->parent->parent) continue;

		// Get the bone parent's index.
		const int parentId = bones[boneId]->parent->index;
		
		// Get the world positions of the bone and its parent.
		const Vector3 pos  = bones[boneId  ]->defaultTransform.GetPosition() * bones[boneId  ]->defaultTransform.GetParentMat() * boneMatrices[boneId  ] + offset;
		const Vector3 pos2 = bones[parentId]->defaultTransform.GetPosition() * bones[parentId]->defaultTransform.GetParentMat() * boneMatrices[parentId] + offset;

		// Draw the bone as a line from itself to its parent.
		DrawLine(pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z, 1, 0, 1);
	}
}

Animator& Skeleton::GetAnimator()
{
	return animator;
}

Bone* Skeleton::GetBone(const int& id) const
{
	for (Bone* bone : bones)
		if (bone->index == id) return bone;

	return nullptr;
}

std::vector<Bone*>& Skeleton::GetBones()
{
	return bones;
}

void Skeleton::UpdateBoneMatrices()
{
	boneMatrices.clear();
	if (boneMatrices.capacity() < bones.size())
		boneMatrices.reserve(bones.size());
	
	for (const Bone* bone : bones)
	{
		// Matrix that transforms a position in the following way: global in default pose -> local to bone in default pose -> local to bone in animated pose -> global in animated pose.
		boneMatrices.push_back(bone->defaultTransform.GetWorldMat().Inv4() * bone->boneAnim.GetPoseLocalMat() * bone->defaultTransform.GetLocalMat() * bone->boneAnim.GetParentMat());
	}
}

std::vector<Mat4>& Skeleton::GetBoneMatrices()
{
	return boneMatrices;
}
