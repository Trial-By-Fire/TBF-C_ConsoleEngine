#pragma once


// Macros (Preprocessed Definitions) ---------------------------------------------------------------

// Aliasing

// Allows the aliasing of a data structure to a different typename.
#define alias(_typeToAlias) \
typedef _typeToAlias

// A way to show relationship to alias...
#define as


// Functions

// Entry point for app execution.
#define EntryPoint \
main

// Used to clearly state a function declare.
#define fn

// Used to clearly state paramater declare.
#define parameters

// States what the function will return data if any. (Put void if you don't want to return data).
#define returns(_returnType) \
_returnType


// Memory

/*
Used for defining a non-compile time constant.
Where something is really just said to not be changeable instead of being a true constant.
const are put in read only memory.
*/
#define readonly \
const

// Explicit specification to use a stack allocated object.
#define Stack(_type) \
_type

// Stores the address for a data instance of the specified type.
#define Ptr(_type) \
_type*

// Gets the address from the specified instance.
#define getAddress(_instance) \
&_instance

// Gets the data instance (instantiated object) from the specified address.
#define val(_address) \
*_address

//////////////////////////////////// End of Macros   ///////////////////////////////////////////////



// Aliases

// Used as the return value for the result code code of execution.
alias(enum ExecFlags_Def) as ExecFlags;



// Enumerators 

enum ExecFlags_Def
{
	ExecFlags_Success = 0,
};
