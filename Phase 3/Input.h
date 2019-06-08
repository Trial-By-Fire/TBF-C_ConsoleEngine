#pragma once

// Includes

#include <stdbool.h>

// Trial By Fire

#include "C_Assist.h"



// Aliases

alias(struct InputData_Def) as InputData;



// Structures

struct InputData_Def
{
	char lastKeyPressed;
};



// Public Instances

Global(InputData) Input_;


// Functions

fn returns(bool) KeyboardHit parameters(void);

fn returns(int) GetKeyPress parameters(void);
