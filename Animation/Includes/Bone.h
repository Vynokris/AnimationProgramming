#pragma once

#include <vector>
#include <string>

struct Bone
{
	int boneId;
	std::string boneName;

	float boneMass;
	float boneLength;

	Bone* parentBone;
	std::vector<Bone*> childBones;

	Bone(const int& id, const std::string& name, const float& mass, const float& length, Bone* parent, std::vector<Bone*> childs) 
	{
		boneId = id;
		boneName = name;

		boneMass = mass;
		boneLength = length;

		parentBone = parent;
		childBones = childs;
	}

	~Bone() 
	{
		delete parentBone;

		for (Bone* child : childBones)
			delete child;
	}
};