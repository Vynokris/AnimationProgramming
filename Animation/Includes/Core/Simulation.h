#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Engine.h"
#include "Animation/Skeleton.h"

struct ENGINE_API SGlobalVariables;

class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() = default;

	virtual void Initialize() {}
	virtual void Update(const float& deltaTime) {}
};

class CSimulation : public ISimulation
{
public:
	int      frameCounter = 0;
	int      selectedBone = 1;
	Skeleton skeleton;
	Vector3  skeletonDrawOffset = { 100, 0, 0 };

	Quaternion lerpStart;
	Quaternion lerpDest;

	void Initialize() override;
	void Update(const float& deltaTime) override;
	static void DrawGizmo(const int& x, const int& y, const int& z);
	void DrawSkeleton();
};

#endif