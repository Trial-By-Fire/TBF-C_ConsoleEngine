// Parent Header
#include "Core.h"



// Includes

// C Standard Library

#include <stdio.h>

// Trial By Fire

#include "FundamentalTypes.h"
#include "CString.h"
#include "Input.h"
#include "Memory.h"
#include "Renderer.h"
#include "Timing.h"



// Private Instances

BSS
(
	bool Exist;   // Used by the cycler to the determine if the engine should persist.
)



// Functions

// The Engine Loop
fn returns(void) Cycler parameters(void)
{
	Exist = true;

	while (Exist == true)
	{
		TakeSnapshot(Snapshot_Initial);

		// Update Input

		if (KeyboardHit())
		{
			Input_.lastKeyPressed = (char)GetKeyPress();
		}

		// Process Input

		if (Input_.lastKeyPressed == 'q')
		{
			Exist = false;
		}

		// Update UI

		// Update Physics

		// Update State

		ProcessRenderer();

		TakeSnapshot(Snapshot_End);

		ProcessCycleTiming();
	}

	return;
}

fn returns(void) SetupEngineModules parameters(void)
{
	SetupStartMessage();

	SetupTiming();

	SetupRenderer();
}

fn returns(void) Launch_V3 parameters(void)
{
	SetupEngineModules();

	Cycler();

	printf("Exiting Game Engine: Press enter key to contiue.");

	getchar();

	return;
}
