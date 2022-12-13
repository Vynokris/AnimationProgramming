#include "Animation/Skeleton.h"

#include <iostream>
#include <algorithm>

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
		std::cout << "AddBone: " << bone->name << " with id: " << bone->index << std::endl;
	}
}

void Skeleton::RemoveBone(const int& id)
{
	Bone* bone = GetBone(id);
	if (!DoesBoneExist(bone)) return;

	std::cout << "RemoveBone: " << bone->name << std::endl;
	bones.erase(std::remove(bones.begin(), bones.end(), bone), bones.end());

	delete bone;
}

Bone* Skeleton::GetBone(const int& id) const
{
	for (Bone* bone : bones)
		if (bone->index == id) return bone;

	return nullptr;
}

std::vector<Bone*> Skeleton::GetBones()
{
	return bones;
}

bool Skeleton::DoesBoneExist(const Bone* bone)
{
	return std::find(bones.begin(), bones.end(), bone) != bones.end();
}
