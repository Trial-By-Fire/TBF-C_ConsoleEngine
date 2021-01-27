// Parent Header
#include "Memory.h"



// Static Data

// Private

Data()

	MemoryBlockArray GlobalMemory =
	{ NULL, 0U };



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

fn returns( Ptr(void) ) Reallocate parameters( Ptr(void)  _memoryToReallocate, DataSize _sizeDesired)
{
	return Heap(realloc(_memoryToReallocate, _sizeDesired));
}

fn returns( Ptr(void) ) Internal_Memory_FormatByFill parameters(Ptr(void) _memoryAddress, sInt _fillValue, DataSize _sizeOfData)
{
	return memset(_memoryAddress, _fillValue, _sizeOfData);
}

fn returns( Ptr(void) ) Memory_FormatWithData parameters(Ptr(void) _memoryAddress, ro Ptr(void) _dataSource, DataSize _sizeOfData)
{
	return memcpy(_memoryAddress, _dataSource, _sizeOfData);
}

// Memory Allocation Array

fn returns(void) MemoryBlockArray_Add parameters(Ptr(MemoryBlockArray) _memoryArray, Ptr(MemoryBlock) _memoryAllocation)
{
	if (_memoryArray->Array == NULL)
	{
		_memoryArray->Array = Heap() AllocateMemory(sizeof(MemoryBlock));

		_memoryArray->Length = 1;
	}
	else
	{
		Stack()
			Address resizeIntermediary = Heap() Reallocate(_memoryArray->Array, _memoryArray->Length + 1);

		if (resizeIntermediary != NULL)
		{
			_memoryArray->Array = resizeIntermediary;

			_memoryArray->Length++;
		}
		else
		{
			perror("Failed to reallocate the global memory array. Exiting...");
		}
	}
}

fn returns(Ptr(MemoryBlock)) MemoryBlockArray_LastEntry parameters(Ptr(MemoryBlockArray) _memoryArray)
{
	return getAddress(_memoryArray->Array[_memoryArray->Length - 1]);
}

// Memory Management

fn returns(Address) Internal_ScopedAllocate(Ptr(MemoryBlockArray) _scopedMemory, DataSize _sizeOfAllocation)
{
	if (_scopedMemory->Array == NULL)
	{
		_scopedMemory->Array = Heap() AllocateMemory(sizeof(Ptr(MemoryBlock)));

		_scopedMemory->Length = 1;
	}
	else
	{
		Stack()
			Address resizeIntermediary = Heap() Reallocate(_scopedMemory->Array, sizeof(Ptr(MemoryBlock)) * (_scopedMemory->Length + 1));

		if (resizeIntermediary != NULL)
		{
			_scopedMemory->Array = resizeIntermediary;

			_scopedMemory->Length++;
		}
		else
		{
			perror("Failed to reallocate the global memory array. Exiting...");
		}
	}

	_scopedMemory->Array[_scopedMemory->Length - 1] = Heap() AllocateMemory(sizeof(MemoryBlock));

	Stack()
		Ptr(MemoryBlock) newBlock = _scopedMemory->Array[_scopedMemory->Length - 1];

	newBlock->Size     = _sizeOfAllocation;
	newBlock->Location = Heap() AllocateMemory(_sizeOfAllocation);

	if (newBlock->Location != NULL)
	{
		return newBlock->Location;
	}
	else
	{
		perror("Failed to globally allocate memory.");

		exit(1);
	}
}

fn returns(void) ScopedDeallocate(Ptr(MemoryBlockArray) _scopedMemory)
{
	for (DataSize index = 0; index < _scopedMemory->Length; index++)
	{
		Deallocate(_scopedMemory->Array[index]->Location);

		Deallocate(_scopedMemory->Array[index]);
	}

	Deallocate(_scopedMemory->Array);

	return;
}

fn returns(Address) Internal_GlobalAllocate parameters(DataSize _sizeOfAllocation)
{
	if (GlobalMemory.Array == NULL)
	{
		GlobalMemory.Array = Heap() AllocateMemory(sizeof(Ptr(MemoryBlock)));

		GlobalMemory.Length = 1;
	}
	else
	{
		Stack()
			Address resizeIntermediary = Heap() Reallocate(GlobalMemory.Array, sizeof(Ptr(MemoryBlock)) * (GlobalMemory.Length + 1));

		if (resizeIntermediary != NULL)
		{
			GlobalMemory.Array = resizeIntermediary;

			GlobalMemory.Length++;
		}
		else
		{
			perror("Failed to reallocate the global memory array. Exiting...");
		}
	}

	GlobalMemory.Array[GlobalMemory.Length -1] = Heap() AllocateMemory(sizeof(MemoryBlock));

	Stack()
		Ptr(MemoryBlock) newBlock = GlobalMemory.Array[GlobalMemory.Length -1];
		
	newBlock->Size     = _sizeOfAllocation;
	newBlock->Location = Heap() AllocateMemory(_sizeOfAllocation);

	if (newBlock->Location != NULL)
	{
		return newBlock->Location;
	}
	else
	{
		perror("Failed to globally allocate memory.");

		exit(1);
	}
}

fn returns(void) GlobalDeallocate parameters(void)
{
	for (DataSize index = 0; index < GlobalMemory.Length; index++)
	{
		Deallocate(GlobalMemory.Array[index]->Location);

		Deallocate(GlobalMemory.Array[index]);
	}

	Deallocate(GlobalMemory.Array);

	return;
}
