// Parent Header
#include "Memory.h"



// Private Instances

Data
(
	MemoryBlock StaticBlock = ,
	{ NULL, { NULL, 0U }, 0U };
)



// Functions

fn returns( Ptr(void) ) AllocateMemory parameters(DataSize _amountToAllocate)
{
	return Heap( malloc(_amountToAllocate) );
}

fn returns(void) Deallocate parameters(Ptr(void) _addressToData)
{
	Heap( free(_addressToData) );

	return;
}

fn returns(void) AddressTable_Add parameters(Ptr(AddressTable) _addressTable, Ptr(void) _addressToAdd)
{
	if (_addressTable->addresses == NULL)
	{
		_addressTable->addresses = Heap( AllocateMemory( sizeof(Ptr(void)) ) );

		_addressTable->addresses[0] = _addressToAdd;

		_addressTable->tableLength = 1U;
	}
	else
	{
		_addressTable->tableLength++;

		Ptr(void) reallocIntermediary = Heap( realloc(_addressTable->addresses, sizeof(Ptr(void)) * _addressTable->tableLength) );

		if (reallocIntermediary != NULL)
		{
			_addressTable->addresses = reallocIntermediary;
		}

		_addressTable->addresses[_addressTable->tableLength - 1] = _addressToAdd;
	}

	return;
}

fn returns( Ptr(void) ) AddresssTable_LastAddress parameters(Ptr(AddressTable) _addressTable)
{
	return _addressTable->addresses[_addressTable->tableLength - 1];
}

fn returns(void) AddressTable_Deallocate parameters(Ptr(AddressTable) _addressTable)
{
	if (_addressTable->addresses != NULL)
	{
		Heap( Deallocate(_addressTable->addresses) );
	}

	return;
}

fn returns(Ptr(void)) Internal_ScopedAllocate(Ptr(MemoryBlock) _scopedBlock, DataSize _sizeOfAllocation)
{
	if (_scopedBlock->address == NULL)
	{
		_scopedBlock->address = Heap( AllocateMemory(_sizeOfAllocation) );

		_scopedBlock->size = _sizeOfAllocation;

		Heap( AddressTable_Add(getAddress(_scopedBlock->objectTable), _scopedBlock->address) );

		return _scopedBlock->address;
	}
	else
	{
		Ptr(void) reallocIntermediary = Heap( realloc(_scopedBlock->address, _scopedBlock->size + _sizeOfAllocation) );

		if (reallocIntermediary != NULL)
		{
			_scopedBlock->address = reallocIntermediary;
		}
		else
		{
			perror("Failed to reallocate static block. Exiting...");

			exit(1);
		}

		Ptr(void) newLocation = (Ptr(Byte))_scopedBlock->address + _scopedBlock->size;

		Heap( AddressTable_Add(getAddress(_scopedBlock->objectTable), newLocation) );

		_scopedBlock->size += _sizeOfAllocation;

		return newLocation;
	}
}

fn returns(void) ScopedDeallocate(Ptr(MemoryBlock) _scopedBlock)
{
	Heap( Deallocate(_scopedBlock->address) );

	Heap( AddressTable_Deallocate(getAddress(_scopedBlock->objectTable)) );

	return;
}

fn returns(Ptr(void)) Internal_StaticAllocate(DataSize _sizeOfAllocation)
{
	if (StaticBlock.address == NULL)
	{
		StaticBlock.address = Heap( AllocateMemory(_sizeOfAllocation) );

		StaticBlock.size = _sizeOfAllocation;

		Heap( AddressTable_Add(getAddress(StaticBlock.objectTable), StaticBlock.address) );

		return StaticBlock.address;
	}
	else
	{
		Ptr(void) reallocIntermediary = Heap( realloc(StaticBlock.address, StaticBlock.size + _sizeOfAllocation) );

		if (reallocIntermediary != NULL)
		{
			StaticBlock.address = reallocIntermediary;
		}
		else
		{
			perror("Failed to reallocate static block. Exiting...");

			exit(1);
		}

		Ptr(void) newLocation = (Ptr(Byte))StaticBlock.address + StaticBlock.size;

		Heap( AddressTable_Add(getAddress(StaticBlock.objectTable), newLocation) );

		StaticBlock.size += _sizeOfAllocation;

		return newLocation;
	}
}

fn returns(void) StaticDeallocate parameters(void)
{
	Heap( Deallocate(StaticBlock.address) );

	Heap( AddressTable_Deallocate(getAddress(StaticBlock.objectTable)) );

	return;
}
