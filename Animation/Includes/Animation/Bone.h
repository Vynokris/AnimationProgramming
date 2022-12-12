#pragma once

#include "Maths/Transform.h"
#include <vector>

struct Bone
{
public:
	int index;
	std::string name;
	Maths::Transform transform;
	Bone* parent = nullptr;
	std::vector<Bone*> children;

	Bone(const int& _index, const std::string& _name, const Transform& _transform) 
		: index(_index), name(_name), transform(_transform) {}
	~Bone() {}

	void UpdateChildrenTransform(const Mat4& parentMat);
};