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
private:
	Skeleton skeleton;
	
public:
	void Initialize() override;
	
	void Update(float deltaTime) override;
	
	void DrawGizmo(const Vector3& offset, const float& size) const;
	void ShowImGui(const float& deltaTime);
};

#endif