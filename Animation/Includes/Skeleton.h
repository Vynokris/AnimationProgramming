#pragma once

#include "Bone.h"

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

	bool BoneExist(const Bone* bone);

	Bone* GetBone                 (const int& id);
	std::vector<Bone*> GetSkeleton();

private:

};