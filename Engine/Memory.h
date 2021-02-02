#pragma once


// Includes

#include "LAL.h"
#include "Input.h"
#include "Renderer.h"
#include "Timing.h"



// Public



// Aliases (Typedefs)

typedef struct MemoryBlock_Def MemoryBlock;

typedef struct MemoryBlockArray_Def MemoryBlockArray;



// Structures

struct MemoryBlock_Def
{
	void* Location;

	size_t Size;
};

struct MemoryBlockArray_Def
{
	MemoryBlock** Array;

	size_t Length;
};



// Static Data



// Functions

// C-API

void* Internal_AllocateMemory(size_t _amountToAllocate    );
void  Deallocate             (void*    _memoryToDeallocate);

void* Internal_Memory_FormatByFill  (void* _memoryAddress,       sInt  _fillValue,  size_t _sizeOfData);
void* Internal_Memory_FormatWithData(void* _memoryAddress, const void* _dataSource, size_t _sizeOfData);

// Memory Allocation Array

MemoryBlock* MemoryBlockArray_Add       (MemoryBlockArray* _memoryArray);
MemoryBlock* MemoryBlockArray_LastEntry (MemoryBlockArray* _memoryArray);
void         MemoryBlockArray_Deallocate(MemoryBlockArray* _memoryArray);

// Memory Management

void* Internal_ScopedAllocate(MemoryBlockArray* _scopedAllocations, size_t _sizeOfAllocation);
void  ScopedDeallocate       (MemoryBlockArray* _scopedAllocations                          );

void* Internal_GlobalAllocate  (                 size_t _sizeOfAllocation   );
void* Internal_GlobalReallocate(void* _location, size_t _sizeForReallocation);
void  GlobalDeallocate         (void                                        );



// Macros

#define AllocateMemory(_type, _numberToAllocate) \
(_type*)Internal_AllocateMemory(_numberToAllocate * sizeof(_type))

#define GlobalAllocate(_type, _numberToAllocate) \
(_type*)Internal_GlobalAllocate(sizeof(_type) * _numberToAllocate)

#define GlobalReallocate(_type, _address, _numberToReallocate) \
(_type*)Internal_GlobalReallocate(_address, sizeof(_type) * _numberToReallocate)

#define ScopedAllocate(_type, _numberToAllocate)  \
(_type*)Internal_ScopedAllocate(&scopedMemory, sizeof(_type) * _numberToAllocate)

#define Memory_FormatByFill(_type, _memoryAddress, _fillValue, _sizeOfAllocation) \
(_type*)Internal_Memory_FormatByFill(_memoryAddress, _fillValue, sizeof(_type) * _sizeOfAllocation)

#define Memory_FormatWithData(_type, _memoryAddress, _dataSource, _numberToAllocate) \
(_type*)Internal_Memory_FormatWithData(_memoryAddress, _dataSource, _numberToAllocate * sizeof(_type))

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
