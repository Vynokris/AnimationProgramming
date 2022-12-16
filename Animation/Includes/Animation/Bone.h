#pragma once

#include "Maths/Transform.h"
#include <vector>
class Animator;
class Animation;


class Bone
{
public:
	Animator&         animator;
	const size_t      index;
	const std::string name;
	Maths::Transform defaultTransform;
	Maths::Transform animatedTransform;
	
	Bone* parent = nullptr;
	std::vector<Bone*> children;

public:
	Bone(const size_t& boneIndex, const std::string& boneName, Animator& skeletonAnimator);

	void SetChildrenDefaultTransform    (const Maths::Mat4& parentMat = Maths::Mat4(true));
	void UpdateChildrenAnimatedTransform(const Maths::Mat4& parentMat = Maths::Mat4(true));
};
