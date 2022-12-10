#include "Includer.h"

#include "Engine.h"
#include "Simulation.h"
#include <Skeleton.h>

#include <iostream>

class CSimulation : public ISimulation
{
	void Initialize() override
	{
		int spine01 = GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		{
			std::cout << std::endl;

			Skeleton skeleton;

			std::cout << "Skeleton size: " << skeleton.GetSkeleton().size() << std::endl;

			Bone* clavicle = new Bone(0, "Clavicle", 0.25f, 11.f, nullptr, {});
			skeleton.AddBone(clavicle);

			Bone* skull = new Bone(1, "Skull", 0.25f, 11.f, nullptr, {});
			skeleton.AddBone(skull);

			Bone* tmpBone = skeleton.GetBone(1);
			if(skeleton.BoneExist(tmpBone))
				std::cout << "GetBone: " << tmpBone->boneName << std::endl;

			const bool clavicleExist = skeleton.BoneExist(clavicle);
			std::cout << "BoneExist: " << (clavicleExist ? "true" : "false") << std::endl;

			skeleton.RemoveBone(clavicle->boneId);

			std::cout << "Skeleton size: " << skeleton.GetSkeleton().size() << std::endl;
		}
	}

	void Update(const float& DeltaSeconds) override
	{
		DrawGizmo(100, 100, 100);
	}

	static void DrawGizmo(const int& x, const int& y, const int& z)
	{
		DrawLine(0, 0, 0, x, 0, 0, 1, 0, 0);
		DrawLine(0, 0, 0, 0, y, 0, 0, 1, 0);
		DrawLine(0, 0, 0, 0, 0, z, 0, 0, 1);
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

