#pragma once

#include "Maths/Transform.h"
#include <vector>
class Animator;


class Bone
{
public:
	Animator&         animator;
	const int         index;
	const std::string name;
	Transform defaultTransform;
	Transform animTransform;
	
	Bone* parent = nullptr;
	std::vector<Bone*> children;

public:
	Bone(const int& boneIndex, const std::string& boneName, Animator& skeletonAnimator);

	void SetChildrenDefaultTransform(const Mat4& parentMat = Mat4(true));
	void UpdateChildrenAnimation    (const float& deltaTime, const Mat4& parentMat = Mat4(true));

	Mat4 GetLocalMat() const;
	Mat4 GetParentMat() const;
};
