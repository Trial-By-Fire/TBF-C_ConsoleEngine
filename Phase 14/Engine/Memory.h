#pragma once


// Includes

#include "LAL.h"
#include "CString.h"
#include "Input.h"
#include "Renderer.h"
#include "Timing.h"



// Public



// Aliases (Typedefs)

typedef void* Address;

typedef struct MemoryBlock_Def MemoryBlock;

typedef struct MemoryBlockArray_Def MemoryBlockArray;



// Structures

struct MemoryBlock_Def
{
	Address Location;

	DataSize Size;
};

struct MemoryBlockArray_Def
{
	MemoryBlock** Array;

	DataSize Length;
};



// Constant 

#define SizeOf_AllModules \
	sizeof(bool) + SizeOf_CString + SizeOf_InputSystem + SizeOf_Renderer + SizeOf_TimeData 



// Static Data



// Functions

// C-API

void* AllocateMemory(DataSize _amountToAllocate  );
void  Deallocate    (void*    _memoryToDeallocate);

void* Internal_Memory_FormatByFill(void* _memoryAddress,       sInt  _fillValue,  DataSize _sizeOfData);
void* Memory_FormatWithData       (void* _memoryAddress, const void* _dataSource, DataSize _sizeOfData);

// Memory Allocation Array

void         MemoryBlockArray_Add       (MemoryBlockArray* _memoryArray, MemoryBlock* _memoryAllocation);
MemoryBlock* MemoryBlockArray_LastEntry (MemoryBlockArray* _memoryArray                                );
void         MemoryBlockArray_Deallocate(MemoryBlockArray* _memoryArray                                );

// Memory Management

Address Internal_ScopedAllocate(MemoryBlockArray* _scopedAllocations, DataSize _sizeOfAllocation);
void    ScopedDeallocate       (MemoryBlockArray* _scopedAllocations                            );

Address Internal_GlobalAllocate  (                   DataSize _sizeOfAllocation   );
Address Internal_GlobalReallocate(Address _location, DataSize _sizeForReallocation);
void    GlobalDeallocate         (void                                            );



// Macros

#define GlobalAllocate(_type, _numberToAllocate) \
Internal_GlobalAllocate(sizeof(_type) * _numberToAllocate)

#define GlobalReallocate(_type, _address, _numberToReallocate) \
Internal_GlobalReallocate(_address, sizeof(_type) * _numberToReallocate);

#define ScopedAllocate(_type, _numberToAllocate)  \
Internal_ScopedAllocate(&scopedMemory, sizeof(_type) * _numberToAllocate)

#define Memory_FormatByFill(_type, _memoryAddress, _fillValue, _sizeOfAllocation) \
Internal_Memory_FormatByFill(_memoryAddress, _fillValue, sizeof(_type) * _sizeOfAllocation);

#define SmartScope                  \
{					                \
	MemoryBlockArray scopedMemory = \
	{ NULL, 0U };


#define SmartScope_End                              \
	if (scopedMemory.Array != NULL)                 \
	{								                \
		ScopedDeallocate(&scopedMemory); \
	}												\
}
