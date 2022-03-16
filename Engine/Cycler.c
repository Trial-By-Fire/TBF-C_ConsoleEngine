// Parent Header
#include "Cycler.h"


// Includes
#include "C_STL.h"
#include "Memory.h"
#include "Renderer.h"
#include "Timing.h"
#include "State.h"



// Static Data

// Private

bool Exist;   // Sentinel value use to exist core engine loop.



// Functions

// Public

void Cycler_Lapse(void) {
	Exist = false;
}

void Cycler_Initialize(void) {
	while (Exist == true)
	{
		Timing_TakeInitialSnapshot();

		// Update Input

		Input_Update();

		// Update State

		State_Update();
		
		// Update Renderer

		Renderer_Update();

		// Update Timing

		Timing_TakeEndingSnapshot();

		Timing_Update();
	}
}

void Cycler_LoadModule(void) {
	Exist = true;
}
