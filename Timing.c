// Parent Header
#include "Timing.h"



// Includes
#include "Memory.h"
#include "Renderer.h"



// Static Data

// Private

BSS
(
	Ptr(TimingData) Timing;
)



// Function

// Public

fn returns(void) TakeInitialSnapshot parameters(void)
{
	QueryPerformanceCounter(getAddress(Timing->TimeSnapshot_Initial));
}

fn returns(void) TakeEndingSnapshot parameters(vodi)
{
	QueryPerformanceCounter(getAddress(Timing->TimeSnapshot_End));
}

fn returns(void) Timing_LoadModule parameters(void)
{
	Timing = Data_AssignMemory(SizeOf_TimeData);

	SetupTiming();
}

fn returns( Ptr(ro TimingData) ) GetTimingContext(void)
{
	return Timing;
}

fn returns(void) ProcessCycleTiming parameters(void)
{
	Timing->Cycle_TicksElapsed = Timing->TimeSnapshot_End.QuadPart - Timing->TimeSnapshot_Initial.QuadPart;

	Timing->Cycle_Microseconds = (float64)(Timing->Cycle_TicksElapsed * TickToMicroseconds);
	Timing->Cycle_Microseconds = Timing->Cycle_Microseconds / (float64)Timing->TimeFrequency.QuadPart;

	Timing->DeltaTime = (float64)Timing->Cycle_TicksElapsed / (float64)MicrosecondToSecond;

	ProcessRenderTiming(Timing->DeltaTime);
}

fn returns(void) SetupTiming parameters(void)
{
	Timing->Cycle_TicksElapsed = 0;
	Timing->Cycle_Microseconds = 0.0L;
	Timing->DeltaTime = 0.0L;

	QueryPerformanceFrequency(getAddress(Timing->TimeFrequency));

	return;
}
