#pragma once


// Includes

#include "LAL.h"
#include "CString.h"
#include "Input.h"
#include "Renderer.h"
#include "Timing.h"



// Public



// Aliases (Typedefs)

alias( Ptr(void) ) as Address;

alias(struct MemoryBlock_Def) as MemoryBlock;

alias(struct MemoryBlockArray_Def) MemoryBlockArray;



// Structures

struct MemoryBlock_Def
{
	Address Location;

	DataSize Size;
};

struct MemoryBlockArray_Def
{
	Ptr( Ptr(MemoryBlock) ) Array;

	DataSize Length;
};



// Constant 

#define SizeOf_AllModules \
	sizeof(bool) + SizeOf_CString + SizeOf_InputSystem + SizeOf_Renderer + SizeOf_TimeData 



// Static Data



// Functions

// C-API

fn returns( Ptr(void) ) AllocateMemory parameters(DataSize  _amountToAllocate);
fn returns(void)        Deallocate     parameters(Ptr(void) _memoryToDeallocate);

fn returns( Ptr(void) ) Internal_Memory_FormatByFill parameters(Ptr(void) _memoryAddress,    sInt      _fillValue,  DataSize _sizeOfData);
fn returns( Ptr(void) ) Memory_FormatWithData        parameters(Ptr(void) _memoryAddress, ro Ptr(void) _dataSource, DataSize _sizeOfData);

// Memory Allocation Array

fn returns(void            ) MemoryBlockArray_Add        parameters(Ptr(MemoryBlockArray) _memoryArray, Ptr(MemoryBlock) _memoryAllocation);
fn returns(Ptr(MemoryBlock)) MemoryBlockArray_LastEntry  parameters(Ptr(MemoryBlockArray) _memoryArray                                    );
fn returns(void            ) MemoryBlockArray_Deallocate parameters(Ptr(MemoryBlockArray) _memoryArray                                    );

// Memory Management

fn returns(Address) Internal_ScopedAllocate parameters(Ptr(MemoryBlockArray) _scopedAllocations, DataSize _sizeOfAllocation);
fn returns(void   ) ScopedDeallocate        parameters(Ptr(MemoryBlockArray) _scopedAllocations                            );

fn returns(Address) Internal_GlobalAllocate   parameters(                   DataSize _sizeOfAllocation   );
fn returns(Address) Internal_GlobalReallocate parameters(Address _location, DataSize _sizeForReallocation);
fn returns(void   ) GlobalDeallocate          parameters(void                                            );



// Macros

#define GlobalAllocate(_type, _numberToAllocate) \
Internal_GlobalAllocate(sizeof(_type) * _numberToAllocate)

#define GlobalReallocate(_type, _address, _numberToReallocate) \
Internal_GlobalReallocate(_address, sizeof(_type) * _numberToReallocate);

#define ScopedAllocate(_type, _numberToAllocate)  \
Internal_ScopedAllocate(getAddress(scopedMemory), sizeof(_type) * _numberToAllocate)

#define Memory_FormatByFill(_type, _memoryAddress, _fillValue, _sizeOfAllocation) \
Internal_Memory_FormatByFill(_memoryAddress, _fillValue, sizeof(_type) * _sizeOfAllocation);

#define SmartScope                  \
{					                \
	MemoryBlockArray scopedMemory = \
	{ NULL, { NULL, 0U }, 0U };


#define SmartScope_End                              \
	if (scopedMemory.Array != NULL)                 \
	{								                \
		ScopedDeallocate(getAddress(scopedMemory)); \
	}												\
}
