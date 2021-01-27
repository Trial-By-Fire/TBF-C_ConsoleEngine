/*
Language Abstraction Layer

(Previously termed as "C-Assist"
*/



#pragma once



#include "C_STL.h"



// Macros (Preprocessed Definitions) ---------------------------------------------------------------

// Aliasing

// Allows the aliasing of a data structure to a different typename.
#define alias(_typeToAlias) \
typedef _typeToAlias

// A way to show relationship to alias...
#define as 


// Functions

//#define EntryPoint \
main

#define fn \

#define parameters \

#define returns(_returnType) \
_returnType

#define FunctionType(_identifier, _returnType, ...) \
_returnType (_identifier) (__VA_ARGS__)


// Memory

/*
Used for defining a non-compile time constant.
Where something is really just said to not be changeable instead of being a true constant.
const are put in read only memory.
*/
#define ro \
const

// Stores the address for a data instance of the specified type. (Pointer declaration, using indirection operator)
#define Ptr(_type) \
_type*

//Provides a more explicit method for getting a reference.
#define getAddress(_instance) \
&_instance

// Gets the data instance from the specified address (AKA Dereference, using indirection operator)
#define val(_address) \
*_address

// Specifies that this datatype is intended to be allocated within the data segment. 
// (It will allocate and format the memory for you before starting the program)
#define Data()
//__VA_ARGS__

// Specifies that this datatype is intended to be allocated within the BSS segment. 
// (It will allocate the memory only but will not format it for you before starting the program)
#define BSS()
//__VA_ARGS__

// Specify that this datatype is intended to allocated (and possibly formatted if specified to) within the stack. 
// (To be used within the function its within scope for)
#define Stack()
//__VA_ARGS__

// Specify that you are interfacing with the heap. (Directly managing unmanaged memory given by the operating system)
#define Heap(_heapOperation) \
_heapOperation

// Creates a static duration variable accessible to any file or linkage. (Global/File scope Only)
#define foreign \
extern

#define unbound \
static

//////////////////////////////////// End of Macros   ///////////////////////////////////////////////



// Aliases (Typedefs) ------------------------------------------------------------------------------

alias(char) as Byte;

alias(signed           short) as sInt16;
alias(signed long long int  ) as sInt64;

alias(unsigned           int) as uInt  ;
alias(unsigned long long int) as uInt64;

alias(signed int) as sInt;

alias(char) as Key;

alias(float ) as float32;
alias(double) as float64;

alias(size_t) as DataSize;

alias( FunctionType(Void_Function, void, void) );

////////////////////////////////////////////////////////////////////////////////////////////////////
