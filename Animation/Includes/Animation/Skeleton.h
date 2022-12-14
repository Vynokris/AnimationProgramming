#pragma once

#include "Bone.h"
#include <vector>

class Skeleton
{
private:
	Bone*              rootBone;
	std::vector<Bone*> bones;

	Vector3 drawOffset;

public:
	Skeleton();
	~Skeleton();

	Bone* Skeleton::GetRootBone() const;
	void SetRootBone(Bone* bone);
	
	void AddBone   (Bone* bone);
	void RemoveBone(const int& id);

	bool DoesBoneExist(const Bone* bone);

	Bone* GetBone(const int& id) const;
	std::vector<Bone*> GetBones();

	Vector3 GetOffset() const;
	void SetOffset(const Vector3& offset);
};