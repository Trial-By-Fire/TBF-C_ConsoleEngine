#pragma once

// Includes

#include <stdbool.h>

// Trial By Fire

#include "C_Assist.h"



// Aliases

alias(struct InputData_Def) as InputData;


alias (char) as Key;



// Structures

struct InputData_Def
{
	Key lastKeyPressed;
};



// Public Instances

BSS
(
	InputData Input_;
)


// Functions

fn returns(bool) KeyboardHit parameters(void);

fn returns(Key ) GetKeyPress parameters(void);
