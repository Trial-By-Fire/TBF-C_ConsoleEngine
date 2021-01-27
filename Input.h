#pragma once



// Includes

#include "C_STL.h"
#include "Windows_Includes.h"
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

fn returns(void) Input_LoadModule parameters(void);

fn returns(Ptr(ro InputData)) GetInputContext(void);

fn returns(Key) GetKeyPress parameters(void);

fn returns(bool) KeyboardHit parameters(void);

fn returns(void) ProcessInput parameters(void);
