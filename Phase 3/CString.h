#pragma once

// Includes

// Trial By Fire

#include "C_Assist.h"
#include "FundamentalTypes.h"



// Aliases

alias(struct CString_Def) as CString;   // C-Strings with specified pointer to array, and length.



// Structures

struct CString_Def
{
	char array[13];

	uInt64 length;
};



// Public Instances

BSS
(
	CString StartMessage;   // Contains Hello World! message.
)



// Functions

// Sets up start message with the data.
fn returns(void) SetupStartMessage(void);
