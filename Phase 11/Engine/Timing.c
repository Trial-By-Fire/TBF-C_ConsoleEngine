// Parent Header
#include "Timing.h"



// Includes
#include "Memory.h"
#include "Renderer.h"



// Static Data

// Private

BSS()

	TimingData Timing;



// Forward Declarations

fn returns(void) Timing_InitalizeData parameters(void);



// Functions

// Public

fn returns(ro Ptr(TimingData)) Timing_GetContext(void)
{
	return getAddress(Timing);
}

fn returns(void) Timing_LoadModule parameters(void)
{
	Timing_InitalizeData();
}

fn returns(void) Timing_TakeInitialSnapshot parameters(void)
{
	QueryPerformanceCounter(getAddress(Timing.TimeSnapshot_Initial));
}

fn returns(void) Timing_TakeEndingSnapshot parameters(void)
{
	QueryPerformanceCounter(getAddress(Timing.TimeSnapshot_End));
}

fn returns(void) Timing_Update parameters(void)
{
	Timing.Cycle_TicksElapsed = Timing.TimeSnapshot_End.QuadPart - Timing.TimeSnapshot_Initial.QuadPart;

	Timing.Cycle_Microseconds = (float64)(Timing.Cycle_TicksElapsed * TickToMicroseconds);
	Timing.Cycle_Microseconds = Timing.Cycle_Microseconds / (float64)Timing.TimeFrequency.QuadPart;

	Timing.DeltaTime = (float64)Timing.Cycle_TicksElapsed / (float64)MicrosecondToSecond;

	Renderer_ProcessTiming(Timing.DeltaTime);
}

// Private

fn returns(void) Timing_InitalizeData parameters(void)
{
	Timing.Cycle_TicksElapsed = 0;
	Timing.Cycle_Microseconds = 0.0L;
	Timing.DeltaTime          = 0.0L;

	QueryPerformanceFrequency(getAddress(Timing.TimeFrequency));

	return;
}



// Timer Class

// Functions

// Public

fn returns(bool) Timer_Ended parameters(Ptr(TimerData) _timer)
{
	return 
		Float64_ApproxGreater(_timer->Elapsed, _timer->EndTime) || 
		Float64_ApproxEqual  (_timer->Elapsed, _timer->EndTime)   ;
}

fn returns(void) Timer_Reset parameters(Ptr(TimerData) _timer)
{
	_timer->Elapsed = 0.0L;
}

fn returns(void) Timer_Tick parameters(Ptr(TimerData) _timer)
{
	if (Float64_ApproxEqual(Timing.DeltaTime, 0.000001L) || Float64_ApproxLess(Timing.DeltaTime, 0.000001L))
	{
		_timer->Elapsed = _timer->Elapsed + 0.000001L;

		return;
	}
	else
	{
		_timer->Elapsed = _timer->Elapsed + Timing.DeltaTime;

		return;
	}
}
