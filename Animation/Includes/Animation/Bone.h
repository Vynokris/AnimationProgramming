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
	
	Bone* parent = nullptr;
	std::vector<Bone*> children;

public:
	Bone(const size_t& boneIndex, const std::string& boneName, Animator& skeletonAnimator);

	void SetChildrenDefaultTransform(const Maths::Mat4& parentMat = Maths::Mat4(true));
	void UpdateChildrenAnimation    (Animation* anim, const Maths::Mat4& parentMat = Maths::Mat4(true)) const;

	// Mat4 GetLocalMat() const;
	// Mat4 GetParentMat() const;
};
