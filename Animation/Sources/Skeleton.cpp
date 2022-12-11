#include "Skeleton.h"

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
	if (!BoneExist(bone))
	{
		skeleton.push_back(bone);
		std::cout << "AddBone: " << bone->boneName << " with id: " << bone->boneIndex << std::endl;
		std::cout << "Skeleton size: " << skeleton.size() << std::endl;
	}
}

void Skeleton::RemoveBone(const int& id)
{
	Bone* bone = GetBone(id);
	if (!BoneExist(bone)) return;

	skeleton.erase(std::remove(skeleton.begin(), skeleton.end(), bone), skeleton.end());

	std::cout << "RemoveBone: " << bone->boneName << std::endl;

	if(bone != nullptr) delete bone;
}

Bone* Skeleton::GetBone(const int& id)
{
	for (Bone* bone : skeleton)
		if (bone->boneIndex == id) return bone;

	return nullptr;
}

std::vector<Bone*> Skeleton::GetSkeleton()
{
	return skeleton;
}

bool Skeleton::BoneExist(const Bone* bone)
{
	if (std::find(skeleton.begin(), skeleton.end(), bone) != skeleton.end())
		return true;

	return false;
}
