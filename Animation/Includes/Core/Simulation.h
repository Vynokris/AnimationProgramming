#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Engine.h"
#include "Animation/Skeleton.h"

class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() {}

	virtual void Initialize() {}
	virtual void Update(const float& deltaTime){}
};

class CSimulation : public ISimulation
{
public:
	Skeleton skeleton;

	void Initialize() override;
	void Update(const float& deltaTime) override;
	static void DrawGizmo(const int& x, const int& y, const int& z);
	void DrawSkeleton();
};

#endif