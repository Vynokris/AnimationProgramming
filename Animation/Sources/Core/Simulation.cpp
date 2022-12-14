#include "Utilities/Includer.h"
#include <iostream>

#include "../Externals/imgui/imgui.h"
#include "../Externals/imgui/imconfig.h"
#include "../Externals/imgui/imgui_internal.h"

#include "Core/Engine.h"
#include "Core/Simulation.h"
#include "Maths/Maths.h"
using namespace Maths;


void CSimulation::Initialize()
{
	// TODO: Unresolved external symbol for SetCurrentContext and GetImGUIContext.
	// ImGui::SetCurrentContext((ImGuiContext*)GetImGUIContext());
	
	for (size_t i = 0; i < GetSkeletonBoneCount(); i++)
	{
		// Get the bone's name and index.
		const int   boneIndex = (int)i;
		const char* boneName  = GetSkeletonBoneName(boneIndex);

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
		if (bone->name.find("ik_") != std::string::npos) {
			// Note: This works because all IK bones are at the end of the bone array.
			//       If it wasn't the case, some bone indices would be different from their IDs,
			//       because removing bones from the middle of the array would modify the indices of the following elements.
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

		bone->animation.SetCurrentAnimation(RUN_ANIMATION);
	}

	// Set default pose bone transforms.
	skeleton.GetRootBone()->SetChildrenDefaultTransform();
}

void CSimulation::Update(float deltaTime)
{
	skeleton.UpdateAnimation(deltaTime);
	
	DrawGizmo    ({  55,  0, 0 }, 50);
	skeleton.Draw({ -80, 0, 0 });
}

void CSimulation::DrawGizmo(const Vector3& offset, const float& size)
{
	DrawLine(offset.x, offset.y, offset.z, offset.x+size, offset.y,      offset.z,      1, 0, 0);
	DrawLine(offset.x, offset.y, offset.z, offset.x,      offset.y+size, offset.z,      0, 1, 0);
	DrawLine(offset.x, offset.y, offset.z, offset.x,      offset.y,      offset.z+size, 0, 0, 1);
}

