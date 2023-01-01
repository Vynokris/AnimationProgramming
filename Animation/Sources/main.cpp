#include "Core/Simulation.h"
// Engine.dll, glew32.dll and SDL2.dll are necessary for the program and need to be in the same directory as the exe.

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}
