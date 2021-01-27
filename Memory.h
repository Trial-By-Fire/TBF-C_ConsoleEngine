#pragma once


// Includes

#include "LAL.h"
#include "CString.h"
#include "Input.h"
#include "Renderer.h"
#include "Timing.h"



// Public



// Aliases (Typedefs)

alias(struct MemoryBlock_Def) as MemoryBlock;



// Structures

struct MemoryBlock_Def
{
	Ptr(void) Address;

	uInt64 ByteLocation;   // Has the last address referenced from the data array.

	DataSize Size;   // In Bytes.
};



// Constant 

#define SizeOf_AllModules \
	sizeof(bool) + SizeOf_CString + SizeOf_InputSystem + SizeOf_Renderer + SizeOf_TimeData 



// Static Data



// Forward Declarations

// C-API

fn returns( Ptr(void) ) AllocateMemory parameters(DataSize _amountToAllocate);

fn returns(void) Deallocate parameters(Ptr(void) _memoryToDeallocate);

// Memory Block

fn returns(void) Data_Alloc parameters(void);

fn returns(void) Data_Dealloc parameters(void);

fn returns( Ptr(void) ) Data_AddressAt parameters(Ptr(uInt64) _byteLocation);

fn returns( Ptr(void) ) Data_AssignMemory parameters(DataSize _sizeOfDataType);
