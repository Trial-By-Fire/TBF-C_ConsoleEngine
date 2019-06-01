#pragma once

// Includes

#include <stdbool.h>

// Trial By Fire

#include "C_Assist.h"



// Aliases

alias(struct InputData_Def) as InputData  ;



// Structures

struct InputData_Def
{
	char lastKeyPressed;
};



// Instances

Stack(InputData) _Input;



// Functions

fn returns(bool) KeyboardHit parameters(void);

fn returns(int) GetKeyPress parameters(void);
