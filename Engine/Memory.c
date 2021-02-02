// Parent Header
#include "Memory.h"



// Static Data

// Private

MemoryBlockArray GlobalMemory =
{ NULL, 0U };



// Functions

// Public

// C-API

void* Internal_AllocateMemory(size_t _amountToAllocate)
{
	return malloc(_amountToAllocate);
}

void Deallocate(void* _memoryToDeallocate)
{
	free(_memoryToDeallocate);

	return;
}

void* Internal_Reallocate(void* _memoryToReallocate, size_t _sizeDesired)
{
	return realloc(_memoryToReallocate, _sizeDesired);
}

#define Reallocate(_type, _memoryToReallocate, _numberDesired) \
(_type*)Internal_Reallocate(_memoryToReallocate, _numberDesired * sizeof(_type))

void* Internal_Memory_FormatByFill(void* _memoryAddress, sInt _fillValue, size_t _sizeOfData)
{
	return memset(_memoryAddress, _fillValue, _sizeOfData);
}

void* Internal_Memory_FormatWithData(void* _memoryAddress, const void* _dataSource, size_t _sizeOfData)
{
	return memcpy(_memoryAddress, _dataSource, _sizeOfData);
}

// Memory Allocation Array

MemoryBlock* MemoryBlockArray_Add(MemoryBlockArray* _memoryArray)
{
	if (_memoryArray->Array == NULL)
	{
		_memoryArray->Array = AllocateMemory(MemoryBlock*, 1);

		_memoryArray->Length = 1;
	}
	else
	{
		MemoryBlock** resizeIntermediary = Reallocate(MemoryBlock*, _memoryArray->Array, (_memoryArray->Length + 1) );

		if (resizeIntermediary != NULL)
		{
			_memoryArray->Array = resizeIntermediary;

			_memoryArray->Length++;
		}
		else
		{
			perror("Failed to reallocate the global memory array. Exiting...");

			exit(1);
		}
	}

	_memoryArray->Array[_memoryArray->Length - 1] = AllocateMemory(MemoryBlock, 1);

	return _memoryArray->Array[_memoryArray->Length - 1];
}

MemoryBlock* MemoryBlockArray_LastEntry(MemoryBlockArray* _memoryArray)
{
	return _memoryArray->Array[_memoryArray->Length - 1];
}

// Memory Management

void* Internal_ScopedAllocate(MemoryBlockArray* _scopedMemory, size_t _sizeOfAllocation)
{
	MemoryBlock* newBlock = MemoryBlockArray_Add(_scopedMemory);

	newBlock->Size     = _sizeOfAllocation;
	newBlock->Location = AllocateMemory(Byte, _sizeOfAllocation);

	if (newBlock->Location != NULL)
	{
		return newBlock->Location;
	}
	else
	{
		perror("Failed to scope allocate memory.");

		exit(1);
	}
}

void ScopedDeallocate(MemoryBlockArray* _scopedMemory)
{
	for (size_t index = 0; index < _scopedMemory->Length; index++)
	{
		Deallocate(_scopedMemory->Array[index]->Location);

		Deallocate(_scopedMemory->Array[index]);
	}

	Deallocate(_scopedMemory->Array);

	return;
}

void* Internal_GlobalAllocate(size_t _sizeOfAllocation)
{
	MemoryBlock* newBlock = MemoryBlockArray_Add(&GlobalMemory);
		
	newBlock->Size     = _sizeOfAllocation;
	newBlock->Location = AllocateMemory(Byte, _sizeOfAllocation);

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

void* Internal_GlobalReallocate(void* _location, size_t _sizeForReallocation)
{
	for (size_t index = 0; index < GlobalMemory.Length; index++)
	{
		if (GlobalMemory.Array[index]->Location == _location)
		{
			void* resizeIntermediary = Reallocate(Byte, _location, _sizeForReallocation);

			if (resizeIntermediary != NULL)
			{
				GlobalMemory.Array[index]->Location = resizeIntermediary;

				return GlobalMemory.Array[index]->Location;
			}
			else
			{
				return NULL;
			}
		}
	}

	return NULL;
}

void GlobalDeallocate(void)
{
	for (size_t index = 0; index < GlobalMemory.Length; index++)
	{
		Deallocate(GlobalMemory.Array[index]->Location);

		Deallocate(GlobalMemory.Array[index]);
	}

	Deallocate(GlobalMemory.Array);

	return;
}
