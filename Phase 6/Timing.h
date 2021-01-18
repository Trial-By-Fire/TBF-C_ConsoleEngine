#pragma once



// Includes

#include "OSPlatform.h"
#include "FloatCompare.h"
#include "LAL.h"



// Aliases (Typedefs)

alias(struct TimingData_Def ) as TimingData;



// Structures

struct TimingData_Def
{
	LARGE_INTEGER TimeSnapshot_Initial;
	LARGE_INTEGER TimeSnapshot_End    ;
	LARGE_INTEGER TimeFrequency       ;
	sint64        Cycle_TicksElapsed  ;
	float64       Cycle_Microseconds  ;
	float64       DeltaTime           ;
};



// Constants

#define TickToMicroseconds \
	1000000

#define MicrosecondToSecond \
	10000000

#define SizeOf_TimeData \
	sizeof(TimingData)



// Forward Declarations

fn returns(void) Timing_MakeTimer parameters(void);

fn returns(ro Ptr(TimingData) ) Timing_GetContext parameters(void);

fn returns(void) Timing_LoadModule parameters(void);

fn returns(void) Timing_TakeInitialSnapshot parameters(void);

fn returns(void) Timing_TakeEndingSnapshot parameters(void);
