// Includes ----------------------------------------------------------------------------------------

// C Standard Library

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Windows Library

#include <conio.h>
#include <Windows.h>

// Trial By Fire

#include "../FloatCompare.h"

//////////////////////////////////// End of Includes ///////////////////////////////////////////////



// Macros (Preprocessed Definitions) ---------------------------------------------------------------

// Aliasing

// Allows the aliasing of a data structure to a different typename.
#define alias \
typedef 

// A way to show relationship to alias...
#define as 

// Functions

#define EntryPoint \
main

#define fn \

#define parameters \

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

// Stores the address for a data instance of the specified type. (Pointer declaration, using indirection operator)
#define Ptr(_type) \
_type*

//Provides a more explicit method for getting a reference.
#define getAddress(_instance) \
&_instance

// Gets the data instance from the specified address (AKA Dereference, using indirection operator)
#define val(_address) \
*_address

// Specifies that this datatype is intended to be allocated within the data segment. 
// (It will allocate and format the memory for you before starting the program)
#define Data(_typeOfData) \
_typeOfData

// Specifies that this datatype is intended to be allocated within the BSS segment. 
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

alias char as Byte;

alias long long int as int64;

alias unsigned           int as uInt  ;
alias unsigned long long int as uInt64;

alias char as Key;

alias long double as float64;

alias size_t as DataSize;

alias CONSOLE_SCREEN_BUFFER_INFO as CSBI;

alias enum ExecFlags_Def  as ExecFlags;

alias struct CString_Def     as CString    ;
alias struct MemoryBlock_Def as MemoryBlock;
alias struct TimingData_Def  as TimingData ;
alias struct InputData_Def   as InputData  ;
alias struct ConsoleData_Def as ConsoleData;

////////////////////////////////////////////////////////////////////////////////////////////////////



// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Sucess = 0,
};

////////////////////////////////////////////////////////////////////////////////////////////////////


// Structures

struct CString_Def
{
	Ptr(char) Array;

	uInt64 Length;
};

struct MemoryBlock_Def
{
	Ptr(void) Address;

	uInt64 ByteLocation;   // Has the last address referenced from the data array.

	DataSize Size;   // In Bytes.
};

struct TimingData_Def
{
	LARGE_INTEGER TimeSnapshot_Initial;
	LARGE_INTEGER TimeSnapshot_End    ;
	LARGE_INTEGER TimeFrequency       ;
	int64         Cycle_TicksElapsed  ;
	float64       Cycle_Microseconds  ;
	float64       DeltaTime           ;
};

struct InputData_Def
{
	Key LastPressedKey;
};

struct ConsoleData_Def
{
	// Procedure Data

	HANDLE ConsoleHandle    ;
	DWORD  CharactersWritten;
	COORD  ScreenPos_00     ;
	CSBI   Csbi_instance    ;
	DWORD  ConsoleSize      ;

	// Render Timing

	float64 ConsoleRefeshTimer   ;
	float64 ConsoleRefeshInterval;
};

////////////////////////////////////////////////////////////////////////////////////////////////////



// Constants ---------------------------------------------------------------------------------------

#define TickToMicroseconds \
	1000000

#define MicrosecondToSecond \
	10000000

#define SizeOf_HelloWorld \
	13U

#define SizeOf_CString \
	sizeof(CString)

#define SizeOf_TimeData \
	sizeof(TimingData)

#define SizeOf_InputSystem \
	sizeof(InputData)

#define SizeOf_Renderer \
	sizeof(ConsoleData)

#define SizeOf_Data \
	sizeof(bool) + SizeOf_CString + SizeOf_TimeData + SizeOf_InputSystem + SizeOf_Renderer

////////////////////////////////////////////////////////////////////////////////////////////////////



// Static Data

// Determine size of each group of data.

BSS
( 
	Ptr(MemoryBlock) DataArray;   // Address to full memory block if using single allocation.

	Ptr(bool) Exist;   // Sentinel value use to exit core engine loop.

	Ptr(CString    ) Message ;   // 
	Ptr(TimingData ) Timing  ;
	Ptr(InputData  ) Input   ;
	Ptr(ConsoleData) Renderer;

	// Input System

	Ptr(char) LastKeyPressed;
)

////////////////////////////////////////////////////////////////////////////////////////////////////



// Functions

// Forward Declarations

fn returns(Ptr(void)) AllocateMemory                  parameters(DataSize _amountToAllocate);
fn returns(bool     ) FillRendererCellsWithWhitespace parameters(void                      );
fn returns(bool     ) FormatRendererCells             parameters(void                      );
fn returns(bool     ) UpdateRendererInfo              parameters(void                      );
fn returns(void     ) ResetRendererDrawPosition       parameters(void                      );

// Start Message

fn returns(void) SetupStartMessage parameters(void)
{
	Message->Length = SizeOf_HelloWorld;

	Message->Array = Heap( AllocateMemory(Message->Length) );

	// Setup the values of the message string. 

	Message->Array[0 ] = 'H' ;   // val( (Message + 0) ) = 'H';
	Message->Array[1 ] = 'e' ;
	Message->Array[2 ] = 'l' ;
	Message->Array[3 ] = 'l' ;
	Message->Array[4 ] = 'o' ;
	Message->Array[5 ] = ' ' ;
	Message->Array[6 ] = 'W' ;
	Message->Array[7 ] = 'o' ;
	Message->Array[8 ] = 'r' ;
	Message->Array[9 ] = 'l' ;
	Message->Array[10] = 'd' ;
	Message->Array[11] = '!' ;
	Message->Array[12] = '\0';

	// Once we have the values we print the message.

	return;
}

// Timing

fn returns(void) ProcessCycleTiming parameters(void)
{
	Timing->Cycle_TicksElapsed = Timing->TimeSnapshot_End.QuadPart - Timing->TimeSnapshot_Initial.QuadPart;

	Timing->Cycle_Microseconds = (float64)(Timing->Cycle_TicksElapsed * TickToMicroseconds                      );
	Timing->Cycle_Microseconds =           Timing->Cycle_Microseconds / (float64)Timing->TimeFrequency.QuadPart  ;

	Timing->DeltaTime          = (float64)Timing->Cycle_TicksElapsed / (float64)MicrosecondToSecond;

	if (Float64_ApproxEqual(Timing->DeltaTime, 0.000001L) || Float64_ApproxLess(Timing->DeltaTime, 0.000001L))
	{
		Renderer->ConsoleRefeshTimer = Renderer->ConsoleRefeshTimer + 0.000001L;

		return;
	}
	else
	{
		Renderer->ConsoleRefeshTimer = Renderer->ConsoleRefeshTimer + Timing->DeltaTime;

		return;
	}
}

fn returns(void) SetupTiming parameters(void)
{
	Timing->Cycle_TicksElapsed = 0   ;
	Timing->Cycle_Microseconds = 0.0L;
	Timing->DeltaTime          = 0.0L;

	QueryPerformanceFrequency(getAddress(Timing->TimeFrequency));

	return;
}

// Input

fn returns(bool) KeyboardHit parameters(void)
{
	return (bool)_kbhit();
}

fn returns(Key) GetKeyPress parameters(void)
{
	return (Key)_getch();
}

// Memory

fn returns( Ptr(void) ) AllocateMemory parameters(DataSize _amountToAllocate)
{
	return Heap( malloc(_amountToAllocate) );
}

fn returns(void) Deallocate parameters(Ptr(void) _memoryToDeallocate )
{
	Heap( free(_memoryToDeallocate) );

	return;
}

// Memory Block

fn returns(void) Data_Alloc parameters(void)
{
	DataArray = Heap( AllocateMemory(sizeof(MemoryBlock)) );

	DataArray->Size = SizeOf_Data;

	DataArray->Address = Heap( AllocateMemory(DataArray->Size) );

	DataArray->ByteLocation = 0U;

	return;
}

fn returns(void) Data_Dealloc parameters(void)
{
	if (DataArray->Size > 0)
	{
		Heap( Deallocate(DataArray->Address) );
	}

	Heap( Deallocate(DataArray) );

	return;
}

fn returns( Ptr(void) ) Data_AddressAt parameters(Ptr(uInt64) _byteLocation)
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

fn returns( Ptr(void) ) Data_AssignMemory parameters(DataSize _sizeOfDataType)
{
	if (DataArray->ByteLocation <= DataArray->Size )
	{
		Stack( Ptr(void) ) addressedAssigned = ( ( Ptr(Byte) )DataArray->Address) + DataArray->ByteLocation;

		DataArray->ByteLocation += _sizeOfDataType;

		return addressedAssigned;
	}
	else
	{
		return NULL;
	}
}


// Renderer

fn returns(void) ClearRender parameters(void)
{
	if (UpdateRendererInfo())
	{
		Renderer->ConsoleSize = Renderer->Csbi_instance.dwSize.X * Renderer->Csbi_instance.dwSize.Y;

		if (FillRendererCellsWithWhitespace() && UpdateRendererInfo() && FormatRendererCells())
		{
			ResetRendererDrawPosition();

			return;
		}
		else
		{
			return;   // If any of the conditions fail, return immediately.
		}
	}
}

// Return value tells you if it did the job.
fn returns(bool) FillRendererCellsWithWhitespace parameters(void)
{
	return FillConsoleOutputCharacter
			(
				Renderer->ConsoleHandle     ,
				(TCHAR)' '                  ,
				Renderer->ConsoleSize       ,
				Renderer->ScreenPos_00      ,
	 getAddress(Renderer->CharactersWritten)
			);
}

fn returns(bool) FormatRendererCells parameters(void)
{
	return FillConsoleOutputAttribute
			(
				Renderer->ConsoleHandle            ,
				Renderer->Csbi_instance.wAttributes,
				Renderer->ConsoleSize              ,
				Renderer->ScreenPos_00             ,
	 getAddress(Renderer->CharactersWritten)
			);
}

fn returns(int) print parameters(readonly Ptr(char) _message)
{
	return puts(_message);
}

fn returns(void) RenderFrame parameters(void)
{
	printf("Tick Elapsed        : %llu  \n", Timing  ->Cycle_TicksElapsed);
	printf("Timer      (Seconds): %.7Lf \n", Renderer->ConsoleRefeshTimer);
	printf("Delta Time (Seconds): %.7Lf \n", Timing  ->DeltaTime         );
	printf("Key Pressed         :  %c   \n", Input   ->LastPressedKey    );
	
	return;
}

fn returns(void) ResetRendererDrawPosition parameters(void)
{
	SetConsoleCursorPosition(Renderer->ConsoleHandle, Renderer->ScreenPos_00);
	
	return;
}

fn returns(void) SetupRenderer parameters(void)
{
	Renderer->ConsoleRefeshTimer    = 0.0L;
	Renderer->ConsoleRefeshInterval = 0.1L;

	Renderer->ScreenPos_00.X = 0;
	Renderer->ScreenPos_00.Y = 0;

	Renderer->ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	return Float64_ApproxGreater(Renderer->ConsoleRefeshTimer, Renderer->ConsoleRefeshInterval) || 
		   Float64_ApproxEqual  (Renderer->ConsoleRefeshTimer, Renderer->ConsoleRefeshInterval)   ;
}

fn returns(bool) UpdateRendererInfo parameters(void)
{
	return GetConsoleScreenBufferInfo(Renderer->ConsoleHandle, getAddress(Renderer->Csbi_instance));
}


// Prepare Modules

fn returns (void) PrepareModules parameters(void)
{
	// Exist Sentinel

	Exist = Data_AssignMemory(sizeof(bool));

	val(Exist) = true;

	// Start Message

	Message = Data_AssignMemory(SizeOf_CString);

	SetupStartMessage();

	// Timing
	
	Timing = Data_AssignMemory(SizeOf_TimeData);

	SetupTiming();

	// Input

	Input = Data_AssignMemory(SizeOf_InputSystem);

	Input->LastPressedKey = '\0';

	// Renderer

	Renderer = Data_AssignMemory(SizeOf_Renderer);

	SetupRenderer();

	return;
}


// Engine Cycle

fn returns(void) EngineCycler parameters(void)
{
	while (val(Exist) == true)
	{
		QueryPerformanceCounter(getAddress(Timing->TimeSnapshot_Initial));   // Take initial cycle snapshot of time.

		// Process Input

		if (KeyboardHit())
		{
			Input->LastPressedKey = GetKeyPress();
		}

		if (Input->LastPressedKey == 'q')
		{
			val(Exist) = false;
		}

		// Update UI

		// Update Physics

		// Update State

		// Process Render

		if (ShouldRender())
		{
			ClearRender();

			RenderFrame();

			Renderer->ConsoleRefeshTimer = 0.0L;
		}

		QueryPerformanceCounter(getAddress(Timing->TimeSnapshot_End));   // Take ending cycle snapshot of time.

		ProcessCycleTiming();
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////



// Entry Point

fn returns(ExecFlags) EntryPoint parameters(void)
{
	// Allocate our data array.

	Heap( Data_Alloc() );

	// Setup engine components.

	PrepareModules();

	// Print Start Message

	print(Message->Array);

	// Core Engine Loop

	EngineCycler();

	// Exit Engine

	printf("Exiting Game Engine: Press enter key to continue.");

	getchar();

	// Now that were done before we leave we deallocate the data array.

	Heap( Data_Dealloc() );

	return ExecFlags_Sucess;
}
