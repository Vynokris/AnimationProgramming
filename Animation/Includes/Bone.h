#pragma once

#include <vector>
#include <string>

struct Bone
{
	int boneIndex;
	std::string boneName;

	int parentBoneIndex;

	Bone(const int& index, const std::string& name, int parentIndex) 
	{
		boneIndex = index;
		boneName = name;

		parentBoneIndex = parentIndex;
	}

	~Bone() {}
};