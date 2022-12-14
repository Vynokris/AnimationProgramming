#pragma once

#include "Maths/Transform.h"
#include <vector>

#include "BoneAnim.h"

struct Bone
{
public:
	int index;
	std::string name;
	Transform defaultTransform;
	BoneAnim animation;
	
	Bone* parent = nullptr;
	std::vector<Bone*> children;

public:
	Bone(const int& _index, const std::string& _name, const Transform& _defaultTransform);

	void SetChildrenDefaultTransform(const Mat4& parentMat = Mat4(true));
	void UpdateChildrenAnimation    (const float& deltaTime, const Mat4& parentMat = Mat4(true));

	Mat4 GetLocalMat() const;
	Mat4 GetWorldMat() const;
};
