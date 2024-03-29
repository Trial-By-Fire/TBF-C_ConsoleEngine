#pragma once



// Includes

#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"



// Enums

enum Input_Constants
{
	Input_NumKeysTracked = 6,

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

typedef enum EInputState_Def EInputState;

typedef bool BoolArray_KeySignals[Input_NumKeysTracked];

typedef struct StructOf_KeySignals_Def StructOf_KeySignals;

typedef struct Input_SignalState_Def Input_SignalState;
typedef struct InputData_Def         InputData;

typedef struct Input_KeyStates_Def Input_KeyStates;

typedef void (InputEvent_Function) (EInputState);

typedef InputEvent_Function* InputEvent_FunctionPtr;

typedef InputEvent_FunctionPtr* InputEvent_PtrTo_FunctionPtr;

typedef struct Subscriptions_Def Subscriptions;



// Structures

struct StructOf_KeySignals_Def
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Enter;
	bool Tab;
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
	InputEvent_FunctionPtr* Array;

	size_t Num;
};

struct InputData_Def
{
	// Signal Buffer

	Input_SignalState CurrentSignalState ;
	Input_SignalState PreviousSignalState;

	EInputState KeyStates[Input_NumKeysTracked];

	// Key Event Subscriptions

	Subscriptions KeyEventSubs[Input_NumKeysTracked];
};



// Functions

const InputData* 
Input_GetContext(void);

void Input_LoadModule(void);

void Input_Update(void);

void Input_SubscribeTo(EKeyCode _key, InputEvent_Function* _callbackFunction);

void Input_Unsubscribe(EKeyCode _key, InputEvent_Function* _callbackFunction);
