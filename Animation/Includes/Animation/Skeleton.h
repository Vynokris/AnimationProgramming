#pragma once

#include "Bone.h"
#include <vector>

class Skeleton
{
private:
	std::vector<Bone*> skeleton;
	Bone* rootBone;

public:
	Skeleton();
	~Skeleton();

	void SetRootBone(Bone* bone);
	
	void AddBone   (Bone* bone);
	void RemoveBone(const int& id);

	bool DoesBoneExist(const Bone* bone);

	Bone* GetBone(const int& id);
	std::vector<Bone*> GetBones();

	void UpdateBoneTransforms();
	void SetBoneDefaultMatrices();
};