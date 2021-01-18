#pragma once



// Includes

#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"



// Macros

#define Make_BoolArray(_numBool) \
alias(bool) as BoolArray_##_numBool[_numBool]

#define TBoolArray(_numBool) \
BoolArray_##_numBool




// Enums

enum EInput_Constants
{
	Keys_NumTracked = 4,

	InputState_BufferSize = 10
};

enum EInputState_Def
{
	EInput_None,
	EInput_Released,
	EInput_Pressed,
	EInput_Held
};



// Aliases (Typedefs)

alias(enum EInputState_Def) as EInputState;

alias(struct InputState_RingBuffer_Def) as InputState_RingBuffer;

//Make_BoolArray(Keys_NumTracked);

alias(bool) as BoolArray_KeySignals[Keys_NumTracked];

alias(struct StructOf_KeySignals_4_Def) as StructOf_KeySignals_4;

alias(struct Input_SignalState_Def) as Input_SignalState;
alias(struct InputData_Def)         as InputData;

alias(struct Input_KeyStates_Def) Input_KeyStates;



// Structures

struct StructOf_KeySignals_4_Def
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

struct Input_SignalState_Def
{
	union
	{
		BoolArray_KeySignals  Array;
		StructOf_KeySignals_4 Keys;
	};
};

struct InputState_RingBuffer_Def
{
	EInputState Buffer[InputState_BufferSize];

	uInt Index;
};

struct InputData_Def
{
	// Signal Buffer

	Input_SignalState CurrentSignalState ;
	Input_SignalState PreviousSignalState;

	// Key Input State Ring Buffer

	InputState_RingBuffer KeyStateBuffer[Keys_NumTracked];
};



// Constants

#define SizeOf_InputSystem \
	sizeof(InputData)



// Functions

fn returns(Ptr(ro InputData)) Input_GetContext(void);

//fn returns(Key) Input_GetKeyPress parameters(void);

fn returns(bool) Input_GetKeyTap(EKeyCode _key, DataSize _recordLength);

fn returns(bool) Input_GetKeyPressed_Pattern parameters(EKeyCode _key);

//fn returns(bool) Input_KeyboardHit parameters(void);

fn returns(void) Input_LoadModule parameters(void);

fn returns(void) Input_Update parameters(void);
