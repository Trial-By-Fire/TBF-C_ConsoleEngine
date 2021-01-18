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

BSS()

	bool Exist;   // Sentinel value use to exist core engine loop.



// Functions

// Public

fn returns(void) Cycler_Lapse parameters(void)
{
	Exist = false;
}

fn returns(void) Cycler_Initialize parameters(void)
{
	while (Exist == true)
	{
		Timing_TakeInitialSnapshot();

		// Update Input

		Input_Update();

		// Update UI

		// Update Physics

		// Update State

		State_Update();
		
		// Update Renderer

		Stack()

			ro Ptr(InputData   ) inputContext    = Input_GetContext   ();
			ro Ptr(RendererData) rendererContext = Renderer_GetContext();
			ro Ptr(TimingData  ) timingContext   = Timing_GetContext  ();

		Renderer_WriteToPersistentSection(1, L"Tick Elapsed        : %llu" , timingContext  ->Cycle_TicksElapsed);
		Renderer_WriteToPersistentSection(2, L"Timer      (Seconds): %.7Lf", rendererContext->RefeshTimer       );
		Renderer_WriteToPersistentSection(3, L"Delta Time (Seconds): %.7Lf", timingContext  ->DeltaTime         );
		//Renderer_WriteToPersistentSection(4, L"Key Pressed         : %c"   , inputContext   ->LastPressedKey    );

		Renderer_Update();

		// Update Timing

		Timing_TakeEndingSnapshot();

		Timing_Update();
	}
}

fn returns(void) Cycler_LoadModule parameters(void)
{
	Exist = true;
}

fn returns(void) Cycler_Quit parameters(void)
{
	Exist = false;
}



// Private

fn returns(bool) ShouldQuit parameters(void)
{
	//unbound 
}
