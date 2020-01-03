// Includes ----------------------------------------------------------------------------------------

// C Standard Library

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Windows Library

#include <conio.h>
#include <Windows.h>


// Trial By Fire

#include "FloatCompare.h"

//////////////////////////////////// End of Includes ///////////////////////////////////////////////



// Macros (Preprocessed Definitions) ---------------------------------------------------------------

// Aliasing

// Allows the aliasing of a data structure to a different typename.
#define alias(_typeToAlias) \
typedef _typeToAlias

// A way to show relationship to alias...
#define as


// Functions

#define EntryPoint \
main

// Used to clearly state a function declare.
#define fn

// Used to clearly state parameter declare.
#define parameters

// States what the function will return data if any. (Put void if you don't want to return data).
#define returns(_returnType) \
_returnType


// Memory

/*
Used for defining a non-compile time constant.
Where something is really just said to not be changeable instead of being a true constant.
const are put in read only memory.
*/
#define readonly \
const

// Stores the address for a data instance of the specified type.
#define Ptr(_type) \
_type*

// Gets the address from the specified instance.
#define getAddress(_instance) \
&_instance

// Gets the data instance (instantiated object) from the specified address.
#define val(_address) \
*_address

// Specifies that this datatype is intended to be allocated within the data segement. 
// (It will allocate and format the memory for you before starting the program)
#define Data(_typeOfData) \
_typeOfData

// Specifies that this datatype is intended to be allocated within the BSS segement. 
// (It will allocate the memory only but will not format it for you before starting the program)
#define BSS(_typeOfData) \
_typeOfData

// Specify that this datatype is intended to allocated (and possibly formatted if specified to) within the stack. 
// (To be used within the function its within scope for)
#define Stack(_typeOfData) \
_typeOfData

// Specify that you are interfacing with the heap. (Directly managing unmanaged memory given by the operating system)
#define Heap(_heapOperation) \
_heapOperation

//////////////////////////////////// End of Macros   ///////////////////////////////////////////////



// Aliases (Typedefs) ------------------------------------------------------------------------------

// C Standard Types

alias(char) as Byte;

alias(size_t) as DataSize;

alias(long double) as floatEP;

alias(long long int) as int64;

alias(unsigned           int) as uInt  ;
alias(unsigned long long int) as uInt64;

alias (char) as Key;

// Microsoft

alias(CONSOLE_SCREEN_BUFFER_INFO) as CSBI;

// TBF

alias(enum ExecFlags_Def) as ExecFlags;

alias(struct CString_Def    ) as CString    ;
alias(struct MemoryBlock_Def) as MemoryBlock;
alias(struct TimingData_Def ) as TimingData ;
alias(struct InputData_Def  ) as InputData  ;
alias(struct ConsoleData_Def) as ConsoleData;

////////////////////////////////////////////////////////////////////////////////////////////////////



// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Success = 0,
};

////////////////////////////////////////////////////////////////////////////////////////////////////



// Structures

struct CString_Def
{
	Ptr(char) array;

	uInt64 length;
};

struct MemoryBlock_Def
{
	Ptr(void) address;

	uInt64 byteLocation;

	DataSize size;
};

struct TimingData_Def
{
	LARGE_INTEGER Snapshot_Initital;
	LARGE_INTEGER Snapshot_End     ;
	LARGE_INTEGER Frequency        ;

	int64   Elapsed_Ticks;
	floatEP Elapsed_Micro;

	floatEP deltaTime;
};

struct InputData_Def
{
	Key lastKeyPressed;
};

struct ConsoleData_Def
{
	HANDLE handle     ;
	CSBI   csbi_inst  ;
	DWORD  size       ;
	COORD  zeroCell   ;
	DWORD  charWritten;

	// Render Timing
	floatEP refreshTimer   ;
	floatEP refreshInterval;
};

////////////////////////////////////////////////////////////////////////////////////////////////////



// Constants ---------------------------------------------------------------------------------------

#define TickToMicroseconds \
	1000000

#define MicrosecondToSecond \
	10000000

#define SizeOf_Data \
	sizeof(bool) + sizeof(CString) + sizeof(TimingData) + sizeof(InputData) + sizeof(ConsoleData)

////////////////////////////////////////////////////////////////////////////////////////////////////



// Static Data ------------------------------------------------------------------------------------------

BSS
(
	Ptr(MemoryBlock) DataArray;

	Ptr(bool) Exist;

	Ptr(CString) StartMessage;

	Ptr(TimingData ) Timing  ;
	Ptr(InputData  ) Input   ;
	Ptr(ConsoleData) Renderer;
)

////////////////////////////////////////////////////////////////////////////////////////////////////



// Functions ---------------------------------------------------------------------------------------

// Forward Declarations

fn returns(Ptr(void)) AllocateMemory parameters(DataSize  _amountToAllocate);
fn returns(void     ) Deallocate     parameters(Ptr(void) _addressToData   );


// Start Message -----------------------------------------------------------------------------------

fn returns(void) SetupStartMessage parameters(void)
{
	StartMessage->length = 13U;

	StartMessage->array = Heap( AllocateMemory(StartMessage->length) );

	StartMessage->array[0 ] = 'H' ;
	StartMessage->array[1 ] = 'e' ;
	StartMessage->array[2 ] = 'l' ;
	StartMessage->array[3 ] = 'l' ;
	StartMessage->array[4 ] = 'o' ;
	StartMessage->array[5 ] = ' ' ;
	StartMessage->array[6 ] = 'W' ;
	StartMessage->array[7 ] = 'o' ;
	StartMessage->array[8 ] = 'r' ;
	StartMessage->array[9 ] = 'l' ;
	StartMessage->array[10] = 'd' ;
	StartMessage->array[11] = '!' ;
	StartMessage->array[12] = '\0';

	return;
}


// Timing ------------------------------------------------------------------------------------------

fn returns(void) SetupTiming parameters(void)
{
	Timing->Elapsed_Ticks = 0   ;
	Timing->Elapsed_Micro = 0.0L;
	Timing->deltaTime     = 0.0L;

	QueryPerformanceFrequency(getAddress(Timing->Frequency));

	return;
}

fn returns(void) ProcessCycleTiming parameters(void)
{
	Timing->Elapsed_Ticks = Timing->Snapshot_End.QuadPart - Timing->Snapshot_Initital.QuadPart;

	Timing->Elapsed_Micro  = (floatEP)(Timing->Elapsed_Ticks * TickToMicroseconds);
	Timing->Elapsed_Micro /= (floatEP) Timing->Frequency.QuadPart                 ;	

	Timing->deltaTime      = (floatEP)(Timing->Elapsed_Micro) / (floatEP)MicrosecondToSecond;

	if 
	(
		FloatEP_ApproxEqual(Timing->deltaTime, 0.000001L) || 
		FloatEP_ApproxLess (Timing->deltaTime, 0.000001L)
	)
	{
		Renderer->refreshTimer += + 0.000001L;

		return;
	}
	else
	{
		Renderer->refreshTimer += Timing->deltaTime;

		return;
	}
}

// Input -------------------------------------------------------------------------------------------

fn returns(bool) KeyboardHit parameters(void)
{
	return _kbhit();
}

fn returns(Key) GetKeyPress parameters(void)
{
	return (Key)_getch();
}


// Memory ------------------------------------------------------------------------------------------

fn returns(Ptr(void)) AllocateMemory parameters(DataSize _amountToAllocate)
{
	return Heap( malloc(_amountToAllocate) );
}

fn returns(void) Deallocate parameters(Ptr(void) _addressToData)
{
	Heap( free(_addressToData) );

	return;
}


// Memory Block ---------------------------------------------------------------------------------------

fn returns(void) Data_Alloc parameters(void)
{
	DataArray = Heap( AllocateMemory(sizeof(MemoryBlock)) );

	DataArray->size = SizeOf_Data;

	DataArray->address = Heap( AllocateMemory(DataArray->size) );

	DataArray->byteLocation = 0U;

	return;
}

fn returns(void) Data_Dealloc parameters(void)
{
	if (DataArray->size > 0)
	{
		Heap( Deallocate(DataArray->address) );
	}

	Heap( Deallocate(DataArray) );

	return;
}

fn returns(Ptr(void)) Data_AssignMemory parameters(DataSize _sizeofDataType)
{
	if (DataArray->byteLocation <= DataArray->size)
	{
		Ptr(void) addressAssigned = ( (Ptr(Byte))DataArray->address ) + DataArray->byteLocation;

		DataArray->byteLocation += _sizeofDataType;

		return addressAssigned;
	}
	else
	{
		return NULL;
	}
}


// Renderer ----------------------------------------------------------------------------------------

fn returns(void) ClearRender parameters()
{
	if (GetConsoleScreenBufferInfo(Renderer->handle, getAddress(Renderer->csbi_inst)))
	{
		Renderer->size = Renderer->csbi_inst.dwSize.X * Renderer->csbi_inst.dwSize.Y;

		if
		(
			!FillConsoleOutputCharacter
			(
				Renderer->handle     ,
				(TCHAR)' '           ,
				Renderer->size       ,
				Renderer->zeroCell   ,
	 getAddress(Renderer->charWritten)
			)
		)
		{
			return;
		}

		if (!GetConsoleScreenBufferInfo(Renderer->handle, getAddress(Renderer->csbi_inst)))
		{
			return;
		}

		if
		(
			!FillConsoleOutputAttribute
			(
				Renderer->handle               ,
				Renderer->csbi_inst.wAttributes,
				Renderer->size                 ,
				Renderer->zeroCell             ,
	 getAddress(Renderer->charWritten          )
			)
		)
		{
			return;
		}

		SetConsoleCursorPosition(Renderer->handle, Renderer->zeroCell);

		//Successfuly cleared. Returning to originating routine.

		return;
	}
	else
	{
		return;
	}
}

fn returns(int) print parameters(readonly Ptr(char) _stringToPrint)
{
	return puts(_stringToPrint);
}

fn returns(void) SetupRenderer parameters(void)
{
	Renderer->handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Renderer->zeroCell.X = 0;
	Renderer->zeroCell.Y = 0;

	Renderer->refreshTimer    = 0.0L;
	Renderer->refreshInterval = 0.1L;

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	if 
	(
		FloatEP_ApproxGreater(Renderer->refreshTimer, Renderer->refreshInterval) ||
		FloatEP_ApproxEqual  (Renderer->refreshTimer, Renderer->refreshInterval)
	)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Prepare Modules ---------------------------------------------------------------------------------

fn returns(void) PrepareModules parameters(void)
{
	// Exist

	Exist = Data_AssignMemory(sizeof(Exist));

	val(Exist) = true;

	// Start Message

	StartMessage = Data_AssignMemory(sizeof(CString));

	SetupStartMessage();

	// Timing

	Timing = Data_AssignMemory(sizeof(TimingData));

	SetupTiming();

	// Input

	Input = Data_AssignMemory(sizeof(InputData));

	// Render

	Renderer = Data_AssignMemory(sizeof(Renderer));

	SetupRenderer();

	return;
}

// Engine Cycle ------------------------------------------------------------------------------------

fn returns(void) EngineCycler parameters(void)
{
	while (val(Exist) == true)
	{
		QueryPerformanceCounter(getAddress(Timing->Snapshot_Initital));

		// Update Input

		if (KeyboardHit())
		{
			Input->lastKeyPressed = GetKeyPress();
		}

		// Process Input

		if (Input->lastKeyPressed == 'q')
		{
			val(Exist) = false;
		}

		// Update UI

		// Update Physics

		// Update State

		// Update Render

		if (ShouldRender())
		{
			ClearRender();

			printf("Tick Elasped        : %llu  \n", Timing  ->Elapsed_Ticks );
			printf("Timer      (Seconds): %.7Lf \n", Renderer->refreshTimer  );
			printf("Delta Time (Seconds): %.7Lf \n", Timing  ->deltaTime     );
			printf("Key Pressed         :  %c   \n", Input   ->lastKeyPressed);

			Renderer->refreshTimer = 0.0L;
		}

		QueryPerformanceCounter(getAddress(Timing->Snapshot_End));

		ProcessCycleTiming();
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////



fn returns(ExecFlags) EntryPoint parameters(void)
{
	// Stack

	Heap( Data_Alloc() );

	// Setup engine components.

	PrepareModules();

	// Core Engine Loop

	EngineCycler();


	// Exit Sequence

	Heap( Data_Dealloc() );

	printf("Exiting Game Engine: Press enter key to continue.");

	getchar();

	return ExecFlags_Success;
}

////////////////////////////////////////////////////////////////////////
