#include "Core/Simulation.h"
#include "Maths/Maths.h"
#include <iostream>

int main()
{
	// std::cout << GetRotationMatrix({PI/2, PI/2, PI/2}).ToString() << "\n";
	
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}
