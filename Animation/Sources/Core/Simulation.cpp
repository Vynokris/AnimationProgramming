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

	for (size_t i = 0; i < GetSkeletonBoneCount(); i++)
	{
		// Get the bone's name and index.
		const char* boneName  = GetSkeletonBoneName((int)i);
		const int   boneIndex = GetSkeletonBoneIndex(boneName);

		// Get the bone's position and rotation.
		Vector3    bonePosition;
		Quaternion boneRotation;
		GetSkeletonBoneLocalBindTransform(boneIndex, bonePosition.x, bonePosition.y, bonePosition.z, boneRotation.w, boneRotation.x, boneRotation.y, boneRotation.z);

		// Create the bone.
		Bone* bone = new Bone(boneIndex, boneName, Transform(bonePosition, boneRotation, {1}));

		// Set the skeleton root and discard inverse kinematics bones.
		if (boneIndex == 0) {
			skeleton.SetRootBone(bone);
		}
		if (std::string(boneName).find("ik_") != std::string::npos) {
			delete bone;
			continue;
		}

		// Add the bone to the skeleton.
		skeleton.AddBone(bone);
	}

	for (Bone* bone : skeleton.GetBones()) 
	{
		// Set the bone's parent.
		bone->parent = skeleton.GetBone(GetSkeletonBoneParentIndex(bone->index));

		// Find and set the bone's children.
		// O(n^2)... didn't find a better solution.
		for (Bone* child : skeleton.GetBones()) {
			if (GetSkeletonBoneParentIndex(child->index) == bone->index) {
				bone->children.push_back(child);
			}
		}
	}

	/*
	for (const Bone* bone : skeleton.GetBones()) {
		const Vector3 worldPos = bone->transform.GetPosition() * bone->transform.GetWorldMat();
		const Vector3 rotEuler = bone->transform.GetRotation().ToEuler();
		std::cout << "Bone Index: " << bone->index << " | Name: " << bone->name << " | Parent: " << (bone->parent ? bone->parent->name : "none") << " | World pos: " << roundInt(worldPos.x) << ", " << roundInt(worldPos.y) << ", " << roundInt(worldPos.z) << " " << " | Rotation: " << roundInt(radToDeg(rotEuler.x)) << ", " << roundInt(radToDeg(rotEuler.y)) << ", " << roundInt(radToDeg(rotEuler.z)) << " " << std::endl;
	}
	*/

	lerpStart = skeleton.GetBone(4)->transform.GetRotation() * Quaternion({ 0,  PI/4, 0 });
	lerpDest  = skeleton.GetBone(4)->transform.GetRotation() * Quaternion({ 0, -PI/4, 0 });
}

void CSimulation::Update(const float& deltaTime)
{
	static int incrementationDir = 1;
	frameCounter += incrementationDir;
	if (frameCounter > 5000 || frameCounter <= 0)
		incrementationDir *= -1;
	
	skeleton.GetBone(4)->transform.SetRotation(Quaternion::SLerp(lerpStart, lerpDest, (float)frameCounter / 5000.f));

	skeleton.UpdateBoneTransforms();
	
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
	for (const Bone* bone : skeleton.GetBones())
	{
		// Stop if the bone is the root or the pelvis.
		if (!bone->parent || !bone->parent->parent) continue;
		
		// Get the world positions of the bone and its parent.
		const Vector3 pos  = Vector3() * (bone        ->transform.GetLocalMat() * bone        ->transform.GetWorldMat()) + skeletonDrawOffset;
		const Vector3 pos3 = Vector3() * (bone->parent->transform.GetLocalMat() * bone->parent->transform.GetWorldMat()) + skeletonDrawOffset;

		// Draw the bone as a line from itself to its parent.
		DrawLine(pos.x, pos.y, pos.z, pos3.x, pos3.y, pos3.z, 1, 0, 1);
	}
}
