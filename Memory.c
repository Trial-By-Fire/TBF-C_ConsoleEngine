// Parent Header
#include "Memory.h"



// Static Data

// Private

BSS
(
	Ptr(MemoryBlock) DataArray;
)


// Functions

// Public

// C-API

fn returns( Ptr(void) ) AllocateMemory parameters(DataSize _amountToAllocate)
{
	return Heap(malloc(_amountToAllocate));
}

fn returns(void) Deallocate parameters(Ptr(void) _memoryToDeallocate)
{
	Heap(free(_memoryToDeallocate));

	return;
}

// Memory Block

fn returns(void) Data_Alloc parameters(void)
{
	DataArray = Heap(AllocateMemory(sizeof(MemoryBlock)));

	DataArray->Size = SizeOf_AllModules;

	DataArray->Address = Heap(AllocateMemory(DataArray->Size));

	DataArray->ByteLocation = 0U;

	return;
}

fn returns(void) Data_Dealloc parameters(void)
{
	if (DataArray->Size > 0)
	{
		Heap(Deallocate(DataArray->Address));
	}

	Heap(Deallocate(DataArray));

	return;
}

fn returns(Ptr(void)) Data_AddressAt parameters(Ptr(uInt64) _byteLocation)
{
	if (val(_byteLocation) <= DataArray->Size)
	{
		return (Ptr(Byte))DataArray->Address + val(_byteLocation);
	}
	else
	{
		return NULL;
	}
}

fn returns(Ptr(void)) Data_AssignMemory parameters(DataSize _sizeOfDataType)
{
	if (DataArray->ByteLocation <= DataArray->Size)
	{
		Stack(Ptr(void)) addressedAssigned = ((Ptr(Byte))DataArray->Address) + DataArray->ByteLocation;

		DataArray->ByteLocation += _sizeOfDataType;

		return addressedAssigned;
	}
	else
	{
		return NULL;
	}
}
