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

//Eds Cancer
#include "../FloatCompare.h"

////////////////////////////////////////////


//Macro

//Execution

// Entrypoint for app execution.
#define EntryPoint \
main

//The return value for the entrypoint function.
#define ExecFlags \
int

//Success flag used for entrypoint function's return.
#define ExecFlags_Success \
0


//Memory Related

//Stores the address for a data instance of the specified type.
#define Ptr(_type) \
_type*

////Gets the address from the specified instance.
//#define address(_instance) \
//&_instance

//Gets the data instance from the specified address
#define val(_address) \
*_address

#define AllocateMemory(_numberOfBytesToAllocate) \
malloc(_numberOfBytesToAllocate)

#define Deallocate(_address) \
free(_address)


//Data Related

//Alias for the fundamental bool type.
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

//Function Related

//Used to clearly state a function declare.
#define fn

//Used to clearly state parameter declare.
#define parameters

// States what the function will return data if any. (Put void if you don't want to return data).
#define returns(_returnType) \
_returnType

#define KeyboardHit \
_kbhit

#define GetKeyPress \
_getch


//Console Related

#define print(_string) \
puts(_string)



// EntryPoint: Where you define the execution of your program. (Its also a function. All execution is within some function)

fn returns(ExecFlags) EntryPoint parameters(void)
{
	#define SizeOf_HelloWorld \
	sizeof(char) * 13

	#define SizeOf_TimeData \
	sizeof(LARGE_INTEGER) * 3 + sizeof(int64) + sizeof(floatEP) * 4

	#define SizeOf_InputSystem \
	sizeof(char)

	#define SizeOf_ConsoleData \
	sizeof(HANDLE) + sizeof(DWORD) + sizeof(COORD) + sizeof(CSBI) + sizeof(DWORD) + sizeof(bool) * 2 + sizeof(uInt)
		
	/*
	All data is allocated to a memory space, this can be either a reserved segment of data called a static space, or structures called a stack and heap.
	The data instance is that data that is allocated at runtime, its usually called an object as well.

	The heap is just a reserved space of memory your operating system gives you to use for your program. (Part of your app's addressable space)

	The stack is a structured area of memory the compiler of your program makes for you automatic data instances (where they exist for the life-time of their scope).

	All data instances in the heap have an address to their location(so does the stack and static memory locations).
	This is so that you can find your way to the data and be able to mess with it. (Otherwise its lost and a "leak" occurs)
	*/
	
	Ptr(void) memoryBlock;

	memoryBlock = AllocateMemory( sizeof(bool) + SizeOf_HelloWorld + SizeOf_TimeData + SizeOf_InputSystem + SizeOf_ConsoleData );

	Ptr(bool) exist;

	exist = memoryBlock;

	val(exist) = true;

	/*
	For our first program we want to print a message so lets make a data instance that can hold a set of characters to give to a message function.

	characters are a set of symbols that are represented as an integer value.

	The first character set made for programming is the ASCII set. It holds up to 256 characters. (1 byte or 8 bits of memory)

	Here will define the address to the character data as something called message.
	*/
	Ptr(char) message;

	/*
	First we'll assign the message the address of the data block.
	*/
	message = memoryBlock;

	/*
	Since the first byte of the memory block is being used by exist, we'll have message be assigned to the next available block after the boolean byte.

	Now we have the rest of the memory block to use to hold our message.
	*/
	message = message + 1;

	/*
	Now we need to format the data to the value of our massage.

	We can do that by accessing every address of the start of a character data block (a discrete section of a data instance) that we allocated, and assigning it a character value.
	*/
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

	/*
	Since exist has data with the value of true, we'll go ahead and print (send a character buffer to standard out) our message. (We can do that with the puts function)
	*/
	print(message);


	// Core Loop Prep

	// Timing Stuff

	Ptr(LARGE_INTEGER) timeSnapshot_Initial;
	Ptr(LARGE_INTEGER) timeSnapshot_End    ;
	Ptr(LARGE_INTEGER) timeFrequency       ;
	Ptr(int64        ) cycle_TicksElapsed  ;
	Ptr(floatEP      ) cycle_Microseconds  ;
	Ptr(floatEP      ) deltaTime           ;   //In Seconds.

	timeSnapshot_Initial = (Ptr(LARGE_INTEGER))(message              + 13);
	timeSnapshot_End     =                     (timeSnapshot_Initial + 1 );
	timeFrequency        =                     (timeSnapshot_End     + 1 );
	cycle_TicksElapsed   = (Ptr(int64        ))(timeFrequency        + 1 );
	cycle_Microseconds   = (Ptr(floatEP      ))(cycle_TicksElapsed   + 1 );
	deltaTime            = (Ptr(floatEP      ))(cycle_Microseconds   + 1 );

	val(cycle_TicksElapsed) = 0   ;
	val(cycle_Microseconds) = 0.0L;
	val(deltaTime         ) = 0.0L;

	QueryPerformanceFrequency(timeFrequency);

	#define TickToMicroseconds \
	1000000

	#define MicrosecondToSecond \
	10000000

	// Console Timing

	Ptr(floatEP) consoleRefeshTimer   ;
	Ptr(floatEP) consoleRefeshInterval;

	consoleRefeshTimer    = (Ptr(floatEP))(deltaTime          + 1);
	consoleRefeshInterval = (Ptr(floatEP))(consoleRefeshTimer + 1);

	val(consoleRefeshTimer   ) = 0.0L;
	val(consoleRefeshInterval) = 0.1L;
	

	// Input System

	Ptr(char) lastKeyPressed;

	lastKeyPressed = (Ptr(char))(consoleRefeshInterval + 1);


	// Clear Console Routine

	Ptr(HANDLE) consoleHandle            ;
	Ptr(DWORD ) charactersWritten        ;
	Ptr(COORD ) screenCoordinates        ;   //Home for cursor.
	Ptr(CSBI  ) csbi_instance            ;
	Ptr(DWORD ) consoleSize              ;
	Ptr(bool  ) fillResult               ;
	Ptr(bool  ) attributeResult          ;
	Ptr(uInt  ) clearConsole_ReturnRoutes;

	consoleHandle             = (Ptr(HANDLE))(lastKeyPressed    + 1);
	charactersWritten         = (Ptr(DWORD ))(consoleHandle     + 1);
	screenCoordinates         = (Ptr(COORD ))(charactersWritten + 1);
	csbi_instance             = (Ptr(CSBI  ))(screenCoordinates + 1);
	consoleSize               = (Ptr(DWORD ))(csbi_instance     + 1);
	fillResult                = (Ptr(bool  ))(consoleSize       + 1);
	attributeResult           = (Ptr(bool  ))(fillResult        + 1);
	clearConsole_ReturnRoutes = (Ptr(uInt  ))(attributeResult   + 1);

	screenCoordinates->X = 0;
	screenCoordinates->Y = 0;

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
				val(screenCoordinates),
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
				val(screenCoordinates)   ,
				charactersWritten
			);

		if (val(attributeResult) == false)
		{
			goto ClearConsole_Return;
		}

		SetConsoleCursorPosition(val(consoleHandle), val(screenCoordinates));

		// Successfully cleared. Returning to originating routine.
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

	printf("Exiting Game Engine: Press enter key to continue. PHASE 1 OVER!!!!!!!!!");

	getchar();

	/*
	Were about to stop running the process so lets clean up memory we allocated to prevent a leak. (We tell the OS we are no longer using this allocated memory at the address we give)
	*/
	Deallocate(memoryBlock);
}

////////////////////////////////////////////////////////////////////////