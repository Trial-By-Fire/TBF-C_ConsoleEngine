// Parent Header
#include "Cycler.h"


// Includes
#include "C_STL.h"
#include "Memory.h"
#include "Renderer.h"
#include "Timing.h"



// Static Data

// Private

BSS()

	bool Exist;   // Sentinel value use to exist core engine loop.



// Function

// Public

fn returns(void) Cycler_Lapse parameters(void)
{
	Exist = false;
}

fn returns(void) Cycler_Initialize parameters(void)
{
	while (Exist == true)
	{
		TakeInitialSnapshot();

		ProcessInput();

		// Update UI

		// Update Physics

		// Update State

		ProcessRender();

		TakeEndingSnapshot();

		ProcessCycleTiming();
	}
}

fn returns(void) Cycler_LoadModule parameters(void)
{
	Exist = true;
}