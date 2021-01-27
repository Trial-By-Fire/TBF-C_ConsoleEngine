#pragma once


// Includes

#include "LAL.h"
#include "Memory.h"



// Aliases (Typedefs)

alias(struct CString_Def) as CString;

alias(char) as CString_13[13];

alias(char) as CTS_CString[];

alias(wchar_t) as WideChar;

alias(wchar_t) as CTS_CWString[];



// Structures

struct CString_Def
{
	Ptr(char) Array;

	uInt64 Length;
};



// Constants

#define SizeOf_CString \
	sizeof(CString)



// Functions

fn returns(void) CString_LoadModule parameters(void);
