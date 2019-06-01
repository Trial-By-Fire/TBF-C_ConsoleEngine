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

// Used to clearly state paramater declare.
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

//////////////////////////////////// End of Macros   ///////////////////////////////////////////////



// Aliases (Typedefs) ------------------------------------------------------------------------------

alias(char) as Byte;

alias(long long int) as int64;

alias(unsigned           int) as uInt  ;
alias(unsigned long long int) as uInt64;

alias(long double) as floatEP;

alias(size_t) as DataSize;

alias(CONSOLE_SCREEN_BUFFER_INFO) as CSBI;

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
	char lastKeyPressed;
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



// Globals ------------------------------------------------------------------------------------------

Ptr(MemoryBlock) Stack;

Ptr(bool) Exist;

Ptr(CString) StartMessage;

Ptr(TimingData ) Timing  ;
Ptr(InputData  ) Input   ;
Ptr(ConsoleData) Renderer;

////////////////////////////////////////////////////////////////////////////////////////////////////



// Functions ---------------------------------------------------------------------------------------

// Foward Declarations

fn returns(Ptr(void)) AllocateMemory parameters(DataSize  _amountToAllocate);
fn returns(void     ) Deallocate     parameters(Ptr(void) _addressToData   );


// The Stack ---------------------------------------------------------------------------------------

fn returns(void) Stack_Alloc parameters(void)
{
	Stack = AllocateMemory(sizeof(MemoryBlock));

	Stack->size = SizeOf_Data;

	Stack->address = AllocateMemory(Stack->size);

	return;
}

fn returns(void) Stack_Dealloc parameters(void)
{
	if (Stack->size > 0)
	{
		Deallocate(Stack->address);
	}

	Deallocate(Stack);

	return;
}

fn returns(Ptr(void)) Stack_AddressAt(Ptr(uInt64) _byteLocation)
{
	if (val(_byteLocation) <= Stack->size)
	{
		return ((Ptr(Byte))Stack->address) + val(_byteLocation);
	}
	else
	{
		return NULL;
	}
}


// Start Message -----------------------------------------------------------------------------------

fn returns(void) SetupStartMessage(void)
{
	StartMessage->length = 13U;

	StartMessage->array = AllocateMemory(StartMessage->length);

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
	}
	else
	{
		Renderer->refreshTimer += Timing->deltaTime;
	}
}

// Input -------------------------------------------------------------------------------------------

fn returns(bool) KeyboardHit parameters(void)
{
	return _kbhit();
}

fn returns(int) GetKeyPress parameters(void)
{
	return _getch();
}


// Memory ------------------------------------------------------------------------------------------

fn returns(Ptr(void)) AllocateMemory parameters(DataSize _amountToAllocate)
{
	return malloc(_amountToAllocate);
}

fn returns(void) Deallocate parameters(Ptr(void) _addressToData)
{
	free(_addressToData);

	return;
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

// Engine Cycle ------------------------------------------------------------------------------------

fn returns(void) EngineCycler parameters(void)
{
	while (val(Exist) == true)
	{
		QueryPerformanceCounter(getAddress(Timing->Snapshot_Initital));

		// Update Input

		if (KeyboardHit())
		{
			Input->lastKeyPressed = (char)GetKeyPress();
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

	Stack_Alloc();

	Ptr(uInt64) _byteLocation = AllocateMemory(sizeof(uInt64));

	// Exist

	val(_byteLocation) = 0U;

	Exist = Stack_AddressAt(_byteLocation);

	val(Exist) = true;

	// Start Message

	val(_byteLocation) += 1U;

	StartMessage = Stack_AddressAt(_byteLocation);

	SetupStartMessage();

	// Timing

	val(_byteLocation) += sizeof(CString);

	Timing = Stack_AddressAt(_byteLocation);

	SetupTiming();

	// Input

	val(_byteLocation) += sizeof(TimingData);

	Input = Stack_AddressAt(_byteLocation);

	// Render

	val(_byteLocation) += sizeof(InputData);

	Renderer = Stack_AddressAt(_byteLocation);

	SetupRenderer();

	// Core Engine Loop

	EngineCycler();

	Deallocate(_byteLocation);

	Stack_Dealloc();

	printf("Exiting Game Engine: Press enter key to contiue.");

	getchar();

	return ExecFlags_Success;
}

////////////////////////////////////////////////////////////////////////
