#pragma once



// Includes

// C Standard Library

#include <stdlib.h>

// Trial By Fire

#include "FundamentalTypes.h"



// Aliases

alias(size_t) as DataSize;

alias(struct AddressTable_Def) as AddressTable;
alias(struct MemoryBlock_Def ) as MemoryBlock ;



// Sturtures

struct AddressTable_Def
{
	Ptr( Ptr(void) ) addresses;

	uInt64 tableLength;
};


struct MemoryBlock_Def
{
	Ptr(void) address;

	AddressTable objectTable;

	DataSize size;
};



// Functions

fn returns(Ptr(void)) AllocateMemory parameters(DataSize  _amountToAllocate);
fn returns(void     ) Deallocate     parameters(Ptr(void) _addressToData   );

fn returns(void     ) AddressTable_Add         parameters(Ptr(AddressTable) _addressTable, Ptr(void) _addressToAdd);
fn returns(Ptr(void)) AddressTable_LastAddress parameters(Ptr(AddressTable) _addressTable                         );
fn returns(void     ) AddressTable_Deallocate  parameters(Ptr(AddressTable) _addressTable                         );

fn returns(Ptr(void)) Internal_ScopedAllocate parameters(Ptr(MemoryBlock) _scopedBlock, DataSize _sizeOfAllocation);
fn returns(void     ) ScopedDeallocate        parameters(Ptr(MemoryBlock) _scopedBlock                            );

fn returns(Ptr(void)) Internal_StaticAllocate parameters(DataSize _sizeofAllocation);
fn returns(void     ) StaticDeallocate        parameters(void                      );



// Macros

#define StaticAllocate(_type, _numberToAllocate)                   \
Heap( Internal_StaticAllocate(sizeof(_type) + _numberToAllocate) )


#define ScopedAllocate(_type, _numberToAllocate)                                            \
Heap( Internal_ScopedAllocate(getAddress(scopedBlock), sizeof(_type) * _numberToAllocate) )


#define SmartScope                                        \
{                                                         \
	Stack                                                 \
	( 	                                                  \
		MemoryBlock scopedBlock = ,                       \
		{ NULL, { NULL, 0U }, 0U };                       \
	)


#define SmartScope_End                                      \
	if (scopedBlock.address != NULL)                        \
	{                                                       \
		Heap( ScopedDeallocate(getAddress(scopedBlock)) );  \
	}                                                       \
}