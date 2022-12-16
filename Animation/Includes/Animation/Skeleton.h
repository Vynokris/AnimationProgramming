#pragma once

#include "Bone.h"
#include "Animator.h"
#include <vector>


class Skeleton
{
private:
	Animator           animator;
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

	Animator& GetAnimator();
	Bone*     GetBone(const int& id) const;
	size_t    GetBoneCount() const { return bones.size(); }
	std::vector<Bone*>& GetBones() { return bones; }
	
	void UpdateBoneMatrices();
	std::vector<Mat4>& GetBoneMatrices();
};
