#pragma once



// Includes

#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"



// Enums

enum EInput_Constants
{
	Keys_NumTracked = 5,

	InputState_BufferSize = 10
};

enum EInputState_Def
{
	EInput_None,
	EInput_Released,
	EInput_Pressed,
	EInput_PressHeld
};



// Aliases (Typedefs)

alias(enum EInputState_Def) as EInputState;

alias(bool) as BoolArray_KeySignals[Keys_NumTracked];

alias(struct StructOf_KeySignals_Def) as StructOf_KeySignals;

alias(struct Input_SignalState_Def) as Input_SignalState;
alias(struct InputData_Def)         as InputData;

alias(struct Input_KeyStates_Def) Input_KeyStates;

alias( FunctionType(InputEvent_Function, void, EInputState) );

alias( Ptr(InputEvent_Function)) as InputEvent_FunctionPtr;

alias(struct Subscriptions_Def) as Subscriptions;



// Structures

struct StructOf_KeySignals_Def
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Enter;
};

struct Input_SignalState_Def
{
	union
	{
		BoolArray_KeySignals Array;
		StructOf_KeySignals  Keys;
	};
};

struct InputState_RingBuffer_Def
{
	EInputState Buffer[InputState_BufferSize];

	uInt Index;
};

struct Subscriptions_Def
{
	Ptr(InputEvent_FunctionPtr) Array;

	DataSize Num;
};

struct InputData_Def
{
	// Signal Buffer

	Input_SignalState CurrentSignalState ;
	Input_SignalState PreviousSignalState;

	EInputState KeyStates[Keys_NumTracked];

	// Key Event Subscriptions

	Subscriptions KeyEventSubs[Keys_NumTracked];
};



// Constants

#define SizeOf_InputSystem \
	sizeof(InputData)



// Functions

fn returns(Ptr(ro InputData)) Input_GetContext(void);

fn returns(void) Input_LoadModule parameters(void);

fn returns(void) Input_Update parameters(void);

fn returns(void) Input_SubscribeTo(EKeyCode _key, Ptr(InputEvent_Function) _callbackFunction);

fn returns(void) Input_Unsubscribe(EKeyCode _key, Ptr(InputEvent_Function) _callbackFunction);
