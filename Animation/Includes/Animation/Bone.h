#pragma once

#include "Maths/Transform.h"
#include <vector>

#include "BoneAnim.h"
class Animator;

class Bone
{
public:
	const int         index;
	const std::string name;
	Transform defaultTransform;
	BoneAnim  boneAnim;
	
	Bone* parent = nullptr;
	std::vector<Bone*> children;

public:
	Bone(const int& boneIndex, const std::string& boneName, Animator& skeletonAnimator);

	void SetChildrenDefaultTransform(const Mat4& parentMat = Mat4(true));
	void UpdateChildrenAnimation    (const float& deltaTime, const Mat4& parentMat = Mat4(true));

	Mat4 GetLocalMat() const;
	Mat4 GetWorldMat() const;
};
