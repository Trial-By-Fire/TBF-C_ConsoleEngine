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



// Functions

//fn returns(void) Timing_MakeTimer parameters(void);

fn returns(ro Ptr(TimingData) ) Timing_GetContext parameters(void);

fn returns(void) Timing_LoadModule parameters(void);

fn returns(void) Timing_TakeInitialSnapshot parameters(void);

fn returns(void) Timing_TakeEndingSnapshot parameters(void);

fn returns(void) Timing_Update parameters(void);



// Timer Class

// Aliases (Typedefs)

alias(struct TimerData_Def) TimerData;



// Structs

struct TimerData_Def
{
	float64 Elapsed;
	float64 EndTime;
};



// Functions

fn returns(bool) Timer_Ended parameters(Ptr(TimerData) _timer);

fn returns(void) Timer_Reset parameters(Ptr(TimerData) _timer);

fn returns(void) Timer_Tick parameters(Ptr(TimerData) _timer);

