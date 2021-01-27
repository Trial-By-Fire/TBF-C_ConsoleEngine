// This is a comment, it lets me put some notes with my code to keep sanity + also help future me remember wtf I was doing here, or someone else.
/*
This is a c file. This where you define whats called "implementation". Or how some part of your program is supposed to work.
There is another file type called a header file that lets you organize your code as well... but, for now lets get the basics down here:

Global Scope: AKA File Scope
This is the raw area of your file.

You can define includes, macros, data, and data types, and functions here.

I'm going to choose to separate my code into my own sectors for the sake of organization.
*/

//Includes

// C Standard Library

#include <stdlib.h>
#include <stdio.h>

// Windows Library

#include <conio.h>
#include <Windows.h>

// Trial By Fire

#include "../FloatCompare.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Macro - Processor

//Execution

// Entrypoint for app execution.
#define EntryPoint \
main

// The return value for the entrypoint function.
#define ExecFlags \
int

// Success flag used for entrypoint function's return.
#define ExecFlags_Success \
0


// Memory Related

// Stores the address for a data instance of the specified type.
#define Ptr(_type) \
_type*

// Gets the data instance from the specified address
#define val(_address) \
*_address

#define AllocateMemory(_numberOfBytesToAllocate) \
malloc(_numberOfBytesToAllocate)

#define Deallocate(_address) \
free(_address)


// Data Related

// Alias for the fundamental bool type.
#define bool \
_Bool

#define true \
1

#define false \
0

#define int64 \
long long int

#define uInt \
unsigned int

#define floatEP \
long double

#define CSBI \
CONSOLE_SCREEN_BUFFER_INFO

// Function Related

// Used to clearly state a function declare.
#define fn

// Used to clearly state paramater declare.
#define parameters

// States what the function will return data if any. (Put void if you don't want to return data).
#define returns(_returnType) \
_returnType

#define KeyboardHit \
_kbhit

#define GetKeyPress \
_getch


// Console Related

#define print(_string) \
puts(_string)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Data Addresses

// Determine size of each group of data.

Ptr(void) memoryBlock;   // Address to full memory block if using single allocation.

Ptr(bool) exist;   // Sentinel value use to exist core engine loop.

Ptr(char) message;   // 

// Timing Stuff

Ptr(LARGE_INTEGER) timeSnapshot_Initial;
Ptr(LARGE_INTEGER) timeSnapshot_End    ;
Ptr(LARGE_INTEGER) timeFrequency       ;
Ptr(int64        ) cycle_TicksElapsed  ;
Ptr(floatEP      ) cycle_Microseconds  ;
Ptr(floatEP      ) deltaTime           ;

// Console Timing

Ptr(floatEP) consoleRefeshTimer   ;
Ptr(floatEP) consoleRefeshInterval;

// Input System

Ptr(char) lastKeyPressed;

// Clear Console Routine

Ptr(HANDLE) consoleHandle            ;
Ptr(DWORD ) charactersWritten        ;
Ptr(COORD ) screenPos_00             ;
Ptr(CSBI  ) csbi_instance            ;
Ptr(DWORD ) consoleSize              ;
Ptr(bool  ) fillResult               ;
Ptr(bool  ) attributeResult          ;
Ptr(uInt  ) clearConsole_ReturnRoutes;




// EntryPoint: Where you define the execution of your program. (Its also a function. All execution is within some function)

fn returns(ExecFlags) EntryPoint parameters(void)
{
	// Sentinel Initalization

	exist = AllocateMemory(sizeof(bool));

	val(exist) = true;


	// Message Initalization

	message = AllocateMemory(sizeof(char) * 13);

	val( (message + 0 ) ) = 'H' ;   //This means the same as data(message) = 'H'; I just did it to keep the whitespace aligned / keep an explicit index of what data block were accessing.
	val( (message + 1 ) ) = 'e' ;   //Since every character data block is one byte, we simply increment the address of our message by how far from the first block it is. 
	val( (message + 2 ) ) = 'l' ;   //We can do this cause we restricted the address of message to be a character.
	val( (message + 3 ) ) = 'l' ;   //Since its restricted to be addresssing a character, every time you do numerical operation on the value of the address,
	val( (message + 4 ) ) = 'o' ;   //your saying to increment the address by the size of a character which is in this case 1 byte.
	val( (message + 5 ) ) = ' ' ;
	val( (message + 6 ) ) = 'W' ;
	val( (message + 7 ) ) = 'o' ;
	val( (message + 8 ) ) = 'r' ;
	val( (message + 9 ) ) = 'l' ;
	val( (message + 10) ) = 'd' ;
	val( (message + 11) ) = '!' ;
	val( (message + 12) ) = '\0';


	// Prints the message
	
	print(message);

	Deallocate(message);


	// Core Loop Prep


	// Timing Initalization

	timeSnapshot_Initial = AllocateMemory(sizeof(LARGE_INTEGER));
	timeSnapshot_End     = AllocateMemory(sizeof(LARGE_INTEGER));
	timeFrequency        = AllocateMemory(sizeof(LARGE_INTEGER));
	cycle_TicksElapsed   = AllocateMemory(sizeof(int64        ));
	cycle_Microseconds   = AllocateMemory(sizeof(floatEP      ));
	deltaTime            = AllocateMemory(sizeof(floatEP      ));

	val(cycle_TicksElapsed) = 0   ;
	val(cycle_Microseconds) = 0.0L;
	val(deltaTime         ) = 0.0L;

	QueryPerformanceFrequency(timeFrequency);

	#define TickToMicroseconds \
	1000000

	#define MicrosecondToSecond \
	10000000


	// Console Timing

	consoleRefeshTimer    = AllocateMemory(sizeof(floatEP));
	consoleRefeshInterval = AllocateMemory(sizeof(floatEP));

	val(consoleRefeshTimer   ) = 0.0L;
	val(consoleRefeshInterval) = 0.1L;
	

	// Input System

	lastKeyPressed = AllocateMemory(sizeof(char));


	// Clear Console Routine

	consoleHandle             = AllocateMemory(sizeof(HANDLE));
	charactersWritten         = AllocateMemory(sizeof(DWORD ));
	screenPos_00              = AllocateMemory(sizeof(COORD ));
	csbi_instance             = AllocateMemory(sizeof(CSBI  ));
	consoleSize               = AllocateMemory(sizeof(DWORD ));
	fillResult                = AllocateMemory(sizeof(bool  ));
	attributeResult           = AllocateMemory(sizeof(bool  ));
	clearConsole_ReturnRoutes = AllocateMemory(sizeof(uInt  ));

	screenPos_00->X = 0;
	screenPos_00->Y = 0;

	val(consoleHandle             ) = GetStdHandle(STD_OUTPUT_HANDLE);
	val(clearConsole_ReturnRoutes ) = 0                              ;

	#define ClearConsoleReturn_CoreEngineLoop \
	0


	goto Skip_Section_CoreEngineLoop;

	ClearConsole:

	if (GetConsoleScreenBufferInfo(val(consoleHandle), csbi_instance))
	{
		val(consoleSize) = csbi_instance->dwSize.X * csbi_instance->dwSize.Y;

		val(fillResult) = \
			FillConsoleOutputCharacter
			(
				val(consoleHandle)    ,
				(TCHAR)' '             ,
				val(consoleSize      ),
				val(screenPos_00),
				charactersWritten
			);

		if (val(fillResult) == false)
		{
			goto ClearConsole_Return;
		}

		if (!GetConsoleScreenBufferInfo(val(consoleHandle), csbi_instance))
		{
			goto ClearConsole_Return;
		}

		val(attributeResult) = \
			FillConsoleOutputAttribute
			(
				val(consoleHandle)       ,
				csbi_instance->wAttributes,
				val(consoleSize      )   ,
				val(screenPos_00)   ,
				charactersWritten
			);

		if (val(attributeResult) == false)
		{
			goto ClearConsole_Return;
		}

		SetConsoleCursorPosition(val(consoleHandle), val(screenPos_00));

		//Successfuly cleared. Returning to originating routine.
	}
	
	ClearConsole_Return:

	if (val(clearConsole_ReturnRoutes) == ClearConsoleReturn_CoreEngineLoop)
	{
		goto CoreEngineLoop_ClearConsoleReturn;
	}

	Skip_Section_CoreEngineLoop:


	Core_Engine_Loop:

	if ( val(exist) == true )
	{
		QueryPerformanceCounter(timeSnapshot_Initial);

		//Update Input

		if (KeyboardHit())
		{
			val(lastKeyPressed) = (char)GetKeyPress();
		}

		// Process Input
	
		if (val(lastKeyPressed) == 'q')
		{
			val(exist) = false;
		}

		//Update UI

		//Update Physics

		//Update State

		//Update Render

		if (FloatEP_ApproxGreater(val(consoleRefeshTimer), val(consoleRefeshInterval)) || FloatEP_ApproxEqual(val(consoleRefeshTimer), val(consoleRefeshInterval)))
		{
			val(clearConsole_ReturnRoutes) = ClearConsoleReturn_CoreEngineLoop;

			goto ClearConsole;

			CoreEngineLoop_ClearConsoleReturn:

			printf("Tick Elasped        : %llu  \n", val(cycle_TicksElapsed));
			printf("Timer      (Seconds): %.7Lf \n", val(consoleRefeshTimer));
			printf("Delta Time (Seconds): %.7Lf \n", val(deltaTime         ));
			printf("Key Pressed         :  %c   \n", val(lastKeyPressed    ));

			val(consoleRefeshTimer) = 0.0L;
		}
		
		QueryPerformanceCounter(timeSnapshot_End);

		val(cycle_TicksElapsed) = timeSnapshot_End->QuadPart - timeSnapshot_Initial->QuadPart;

		val(cycle_Microseconds) = (floatEP)(val(cycle_TicksElapsed) * TickToMicroseconds              );
		val(cycle_Microseconds) =           val(cycle_Microseconds) / (floatEP)timeFrequency->QuadPart ;	

		val(deltaTime)          = (floatEP)val(cycle_TicksElapsed) / (floatEP)MicrosecondToSecond;

		if (FloatEP_ApproxEqual(val(deltaTime), 0.000001L) || FloatEP_ApproxLess(val(deltaTime), 0.000001L))
		{
			val(consoleRefeshTimer) = val(consoleRefeshTimer) + 0.000001L;
		}
		else
		{
			val(consoleRefeshTimer) = val(consoleRefeshTimer) + val(deltaTime);
		}

		goto Core_Engine_Loop;
	}

	printf("Exiting Game Engine: Press enter key to contiue. PHASE 1 OVER!!!!!!!!!");

	getchar();

	Deallocate(exist                    );
	Deallocate(timeSnapshot_Initial     );
	Deallocate(timeSnapshot_End         );
	Deallocate(timeFrequency            );
	Deallocate(cycle_TicksElapsed       );
	Deallocate(cycle_Microseconds       );
	Deallocate(deltaTime                );
	Deallocate(consoleRefeshTimer       );
	Deallocate(consoleRefeshInterval    );
	Deallocate(lastKeyPressed           );
	Deallocate(consoleHandle            );
	Deallocate(charactersWritten        );
	Deallocate(screenPos_00             );
	Deallocate(csbi_instance            );
	Deallocate(consoleSize              );
	Deallocate(fillResult               );
	Deallocate(attributeResult          );
	Deallocate(clearConsole_ReturnRoutes);
}

////////////////////////////////////////////////////////////////////////