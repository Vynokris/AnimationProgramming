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
	virtual void Update(float deltaTime) {}
};

class CSimulation : public ISimulation
{
public:
	Skeleton walkSkeleton;
	Skeleton runSkeleton;
	
	Quaternion lerpStart;
	Quaternion lerpDest;

	void Initialize() override;
	void Update(float deltaTime) override;
	static void DrawGizmo(const int& x, const int& y, const int& z);
	
	void DrawSkeleton(Skeleton& skeleton);
	void SetupSkeleton(Skeleton& skeleton, const char* animation, const Vector3& offset);
};

#endif