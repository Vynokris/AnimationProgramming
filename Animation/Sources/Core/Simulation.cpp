#include "Utilities/Includer.h"
#include <iostream>

#include "Core/Engine.h"
#include "Core/Simulation.h"
#include "Maths/Maths.h"
using namespace Maths;


void CSimulation::Initialize()
{
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

		bone->animation.SetCurrentAnimation(WALK_ANIMATION, bone->index);
	}
}

void CSimulation::Update(float deltaTime)
{
	skeleton.GetRootBone()->UpdateChildrenAnimation(deltaTime);
	
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
		const Vector3 pos  = Vector3() * bone        ->GetWorldMat() + skeletonDrawOffset;
		const Vector3 pos2 = Vector3() * bone->parent->GetWorldMat() + skeletonDrawOffset;

		// Draw the bone as a line from itself to its parent.
		DrawLine(pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z, 1, 0, 1);
	}
}
