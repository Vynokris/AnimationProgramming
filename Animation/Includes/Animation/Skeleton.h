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
	std::vector<Maths::Mat4>  boneMatrices;

public:
	Skeleton();
	~Skeleton();

	Bone* GetRootBone() const;
	void  SetRootBone(Bone* bone);
	
	void AddBone      (Bone* bone);
	void RemoveBone   (const int& id);
	bool DoesBoneExist(const Bone* bone);

	void Update(const float& deltaTime);
	void UpdateBoneMatrices();
	void Draw(const Maths::Vector3& offset) const;

	Animator& GetAnimator();
	
	Bone*  GetBone(const size_t& id) const;
	size_t GetBoneCount() const { return bones.size(); }
	std::vector<Bone*>& GetBones() { return bones; }
	std::vector<Maths::Mat4>& GetBoneMatrices();
};
