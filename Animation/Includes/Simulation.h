#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Engine.h"

class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() {}

	virtual void Initialize() {}
	virtual void Update(const float& deltaTime){}
};

#endif