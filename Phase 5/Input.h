#pragma once



// Includes

#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"



// Aliases (Typedefs)

alias(struct InputData_Def  ) as InputData;



// Structures

struct InputData_Def
{
	Key LastPressedKey;
};



// Constants

#define SizeOf_InputSystem \
	sizeof(InputData)



// Forward Declarations

fn returns(Ptr(ro InputData)) Input_GetContext(void);

fn returns(Key) Input_GetKeyPress parameters(void);

fn returns(bool) Input_KeyboardHit parameters(void);

fn returns(void) Input_LoadModule parameters(void);

fn returns(void) Input_Update parameters(void);
