#include "Utilities/Includer.h"
#include <iostream>

#include "Core/Engine.h"
#include "Core/Simulation.h"
#include "Maths/Maths.h"
using namespace Maths;


void CSimulation::Initialize()
{
	/*
	int spine01 = GetSkeletonBoneIndex("spine_01");
	int spineParent = GetSkeletonBoneParentIndex(spine01);
	const char* spineParentName = GetSkeletonBoneName(spineParent);

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
	printf("Spine parent bone : %s\n", spineParentName);
	printf("Anim key count : %ld\n", keyCount);
	printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
	*/

	for (size_t i = 0; i < GetSkeletonBoneCount(); i++) {
		const char* boneName  = GetSkeletonBoneName((int)i);
		const int   boneIndex = GetSkeletonBoneIndex(boneName);

		Vector3    bonePosition;
		Quaternion boneRotation;
		GetSkeletonBoneLocalBindTransform(boneIndex, bonePosition.x, bonePosition.y, bonePosition.z, boneRotation.w, boneRotation.x, boneRotation.y, boneRotation.z);

		Bone* bone = new Bone(boneIndex, boneName, Transform(bonePosition, boneRotation, {1}));

		if (std::strcmp(boneName, "root") == 0)
			skeleton.SetRootBone(bone);

		skeleton.AddBone(bone);
	}

	for (Bone* bone : skeleton.GetBones()) 
	{
		bone->parent = skeleton.GetBone(GetSkeletonBoneParentIndex(bone->index));

		// O(n^2)... didn't find better solution.
		for (Bone* child : skeleton.GetBones()) {
			if (GetSkeletonBoneParentIndex(child->index) == bone->index) {
				bone->children.push_back(child);
			}
		}
	}

	skeleton.UpdateBoneTransforms();

	for (Bone* bone : skeleton.GetBones()) {
		const Vector3 worldPos = bone->transform.GetPosition() * bone->transform.worldMat;
		const Vector3 rotEuler = bone->transform.GetRotation().toEuler();
		std::cout << "Bone Index: " << bone->index << " | Name: " << bone->name << " | Parent: " << (bone->parent ? bone->parent->name : "none") << " | World pos: " << roundInt(worldPos.x) << ", " << roundInt(worldPos.y) << ", " << roundInt(worldPos.z) << " " << " | Rotation: " << roundInt(radToDeg(rotEuler.x)) << ", " << roundInt(radToDeg(rotEuler.y)) << ", " << roundInt(radToDeg(rotEuler.z)) << " " << std::endl;
	}
}

void CSimulation::Update(const float& deltaTime)
{
	DrawGizmo(100, 100, 100);
	DrawSkeleton();
}

void CSimulation::DrawGizmo(const int& x, const int& y, const int& z)
{
	DrawLine(0, 0, 0, (float)x, 0, 0, 1, 0, 0);
	DrawLine(0, 0, 0, 0, (float)y, 0, 0, 1, 0);
	DrawLine(0, 0, 0, 0, 0, (float)z, 0, 0, 1);
}

void CSimulation::DrawSkeleton()
{
	for (Bone* bone : skeleton.GetBones())
	{
		const Vector3 pos  = bone->transform.GetPosition() * bone->transform.worldMat;
		const Vector3 pos2 = (bone->parent ? bone->parent->transform.GetPosition() * bone->parent->transform.worldMat : pos);
		DrawLine(pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z, 1, 0, 1);
	}
}
