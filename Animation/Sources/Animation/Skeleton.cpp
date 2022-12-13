#include "Animation/Skeleton.h"

#include <iostream>
#include <algorithm>

Skeleton::Skeleton()
{
	skeleton = {};
}

Skeleton::~Skeleton()
{
	skeleton.clear();
}

void Skeleton::SetRootBone(Bone* bone)
{
	rootBone = bone;
}

void Skeleton::AddBone(Bone* bone)
{
	if (!DoesBoneExist(bone))
	{
		skeleton.push_back(bone);
		std::cout << "AddBone: " << bone->name << " with id: " << bone->index << std::endl;
	}
}

void Skeleton::RemoveBone(const int& id)
{
	Bone* bone = GetBone(id);
	if (!DoesBoneExist(bone)) return;

	skeleton.erase(std::remove(skeleton.begin(), skeleton.end(), bone), skeleton.end());

	std::cout << "RemoveBone: " << bone->name << std::endl;

	if(bone != nullptr) delete bone;
}

Bone* Skeleton::GetBone(const int& id)
{
	for (Bone* bone : skeleton)
		if (bone->index == id) return bone;

	return nullptr;
}

std::vector<Bone*> Skeleton::GetBones()
{
	return skeleton;
}

void Skeleton::UpdateBoneTransforms()
{
	rootBone->UpdateChildrenTransform(Mat4(true));
}

void Skeleton::SetBoneDefaultMatrices()
{
	rootBone->SetChildrenDefaultMatrices(Mat4(true));
}

bool Skeleton::DoesBoneExist(const Bone* bone)
{
	if (std::find(skeleton.begin(), skeleton.end(), bone) != skeleton.end())
		return true;

	return false;
}
