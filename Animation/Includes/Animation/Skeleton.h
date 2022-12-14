#pragma once

#include "Bone.h"
#include <vector>

class Skeleton
{
private:
	Bone*              rootBone;
	std::vector<Bone*> bones;
	std::vector<Mat4>  boneMatrices;

public:
	Skeleton();
	~Skeleton();

	Bone* GetRootBone() const;
	void  SetRootBone(Bone* bone);
	
	void AddBone      (Bone* bone);
	void RemoveBone   (const int& id);
	bool DoesBoneExist(const Bone* bone);

	void UpdateAnimation(const float& deltaTime);
	void Draw           (const Vector3& offset) const;
	
	Bone* GetBone(const int& id) const;
	std::vector<Bone*>& GetBones();
	
	void UpdateBoneMatrices();
	std::vector<Mat4>& GetBoneMatrices();
};