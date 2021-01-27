#pragma once


// Includes

#include "LAL.h"
#include "Memory.h"



// Aliases (Typedefs)

alias(struct CString_Def) as CString;



// Structures

struct CString_Def
{
	Ptr(char) Array;

	uInt64 Length;
};



// Constants

#define SizeOf_HelloWorld \
	13U

#define SizeOf_CString \
	sizeof(CString)



// Forward Declarations

fn returns(void) CString_PrintStartMessage parameters(void);

fn returns(void) CString_LoadModule parameters(void);

fn returns(void) SetupStartMessage parameters(void);