#include "Utilities/Includer.h"
#include <iostream>

#include "Core/Engine.h"
#include "Core/Simulation.h"

#include "../Externals/imgui/imgui.h"
#include "../Externals/imgui/imconfig.h"
#include "../Externals/imgui/imgui_internal.h"

using namespace Maths;

void CSimulation::Initialize()
{
	ImGui::SetCurrentContext((ImGuiContext*)GetImGUIContext());
	
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
		Bone* boneWalk = new Bone(boneIndex, boneName, Transform(bonePosition, boneRotation, {1}));
		Bone* boneRun = new Bone(boneIndex, boneName, Transform(bonePosition, boneRotation, {1}));

		// Set the skeleton root and discard inverse kinematics bones.
		if (boneIndex == 0) {
			walkSkeleton.SetRootBone(boneWalk);
			runSkeleton.SetRootBone(boneRun);
		}
		if (std::string(boneName).find("ik_") != std::string::npos) {
			delete boneWalk;
			delete boneRun;
			continue;
		}

		// Add the bone to the skeleton.
		walkSkeleton.AddBone(boneWalk);
		runSkeleton.AddBone(boneRun);
	}

	SetupSkeleton(walkSkeleton, WALK_ANIMATION, { 150, 0, 0 });
	SetupSkeleton(runSkeleton, RUN_ANIMATION, { 300, 0, 0 });
}

void CSimulation::Update(float deltaTime)
{
	walkSkeleton.GetRootBone()->UpdateChildrenAnimation(deltaTime);
	runSkeleton.GetRootBone()->UpdateChildrenAnimation(deltaTime);
	
	DrawGizmo(100, 100, 100);
	DrawSkeleton(walkSkeleton);
	DrawSkeleton(runSkeleton);
}

void CSimulation::DrawGizmo(const int& x, const int& y, const int& z)
{
	DrawLine(0, 0, 0, (float)x, 0, 0, 1, 0, 0);
	DrawLine(0, 0, 0, 0, (float)y, 0, 0, 1, 0);
	DrawLine(0, 0, 0, 0, 0, (float)z, 0, 0, 1);
}

void CSimulation::DrawSkeleton(Skeleton& skeleton)
{
	for (const Bone* bone : skeleton.GetBones())
	{
		// Stop if the bone is the root or the pelvis.
		if (!bone->parent || !bone->parent->parent) continue;
		
		// Get the world positions of the bone and its parent.
		const Vector3 pos  = Vector3() * bone        ->GetWorldMat() + skeleton.GetOffset();
		const Vector3 pos2 = Vector3() * bone->parent->GetWorldMat() + skeleton.GetOffset();

		// Draw the bone as a line from itself to its parent.
		DrawLine(pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z, 1, 0, 1);
	}
}

void CSimulation::SetupSkeleton(Skeleton& skeleton, const char* animation, const Vector3& offset)
{
	skeleton.SetOffset(offset);
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

		bone->animation.SetCurrentAnimation(animation);
	}
}
