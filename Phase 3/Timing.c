// Parent Header
#include "Timing.h"



// Includes

// Trial By Fire

#include "floatCompare.h"



// Aliases

alias(struct TimingData_Def) as TimingData;



// Structures

struct TimingData_Def
{
	LARGE_INTEGER Snapshot_Initital;
	LARGE_INTEGER Snapshot_End     ;
	LARGE_INTEGER Frequency        ;

	sInt64   Elapsed_Ticks;
	floatEP  Elapsed_Micro;

	floatEP deltaTime;

	// Render Timing
	floatEP refreshTimer   ;
	floatEP refreshInterval;
};



// Private Instances

BSS
(
	TimingData Timing;
)



// Constants

#define TickToMicroseconds \
	1000000

#define MicrosecondToSecond \
	10000000




// Functions

fn returns(floatEP) DeltaTime parameters(void)
{
	return Timing.deltaTime;
}

fn returns(uInt64) ElapsedTicks parameters(void)
{
	return Timing.Elapsed_Ticks;
}

fn returns(void) ProcessCycleTiming parameters(void)
{
	Timing.Elapsed_Ticks = Timing.Snapshot_End.QuadPart - Timing.Snapshot_Initital.QuadPart;

	Timing.Elapsed_Micro  = (floatEP)(Timing.Elapsed_Ticks * TickToMicroseconds);
	Timing.Elapsed_Micro /= (floatEP) Timing.Frequency.QuadPart                 ;	

	Timing.deltaTime      = (floatEP)(Timing.Elapsed_Micro) / (floatEP)MicrosecondToSecond;

	if 
	(
		FloatEP_ApproxEqual(Timing.deltaTime, 0.000001L) || 
		FloatEP_ApproxLess (Timing.deltaTime, 0.000001L)
	)
	{
		Timing.refreshTimer += + 0.000001L;

		return;
	}
	else
	{
		Timing.refreshTimer += Timing.deltaTime;

		return;
	}
}

fn returns(floatEP) RefreshTimer parameters(void)
{
	return Timing.refreshTimer;
}

fn returns(void) SetupTiming parameters(void)
{
	Timing.Elapsed_Ticks = 0   ;
	Timing.Elapsed_Micro = 0.0L;
	Timing.deltaTime     = 0.0L;

	QueryPerformanceFrequency(getAddress(Timing.Frequency));

	Timing.refreshTimer    = 0.0L;
	Timing.refreshInterval = 0.1L;

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	if
	(
		FloatEP_ApproxGreater(Timing.refreshTimer, Timing.refreshInterval) ||
		FloatEP_ApproxEqual  (Timing.refreshTimer, Timing.refreshInterval)
	)
	{
		Timing.refreshTimer = 0.0L;

		return true;
	}
	else
	{
		return false;
	}
}

fn returns(void) TakeSnapshot parameters(Snapshot _snapshotFor)
{
	switch (_snapshotFor)
	{
		case Snapshot_Initial:
		{
			QueryPerformanceCounter(getAddress(Timing.Snapshot_Initital));

			return;
		}
		case Snapshot_End:
		{
			QueryPerformanceCounter(getAddress(Timing.Snapshot_End));

			return;
		}
	}
}

