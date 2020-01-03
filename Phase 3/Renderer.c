// Parent Header
#include "Renderer.h"



// Includes

// C Standard Library

#include <stdio.h>

// Windows

#include <Windows.h>

// Trial By Fire

#include "Input.h"
#include "Timing.h"



// Aliases

alias(CONSOLE_SCREEN_BUFFER_INFO) as CSBI;

alias(struct ConsoleData_Def) as ConsoleData;



// Structures

struct ConsoleData_Def
{
	HANDLE handle     ;
	CSBI   csbi_inst  ;
	DWORD  size       ;
	COORD  zeroCell   ;
	DWORD  charWritten;
};



// Private Instances

BSS
(
	ConsoleData Renderer;
)



// Functions

fn returns(void) ClearRender parameters()
{
	if (GetConsoleScreenBufferInfo(Renderer.handle, getAddress(Renderer.csbi_inst)))
	{
		Renderer.size = Renderer.csbi_inst.dwSize.X * Renderer.csbi_inst.dwSize.Y;

		if
		(
			!FillConsoleOutputCharacter
			(
				Renderer.handle     ,
				(TCHAR)' '          ,
				Renderer.size       ,
				Renderer.zeroCell   ,
	 getAddress(Renderer.charWritten)
			)
		)
		{
			return;
		}

		if (!GetConsoleScreenBufferInfo(Renderer.handle, getAddress(Renderer.csbi_inst)))
		{
			return;
		}

		if
		(
			!FillConsoleOutputAttribute
			(
				Renderer.handle               ,
				Renderer.csbi_inst.wAttributes,
				Renderer.size                 ,
				Renderer.zeroCell             ,
	 getAddress(Renderer.charWritten          )
			)
		)
		{
			return;
		}

		SetConsoleCursorPosition(Renderer.handle, Renderer.zeroCell);

		//Successfuly cleared. Returning to originating routine.

		return;
	}
}

fn returns(int) print parameters(readonly Ptr(char) _stringToPrint)
{
	return puts(_stringToPrint);
}

fn returns(void) ProcessRenderer parameters(void)
{
	if (ShouldRender())
	{
		ClearRender();

		printf("Tick Elasped        : %llu  \n", ElapsedTicks()         );
		printf("Timer      (Seconds): %.7Lf \n", RefreshTimer()         );
		printf("Delta Time (Seconds): %.7Lf \n", DeltaTime   ()         );
		printf("Key Pressed         :  %c   \n", Input_  .lastKeyPressed);
	}

	return;
}

fn returns(void) SetupRenderer parameters(void)
{
	Renderer.handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Renderer.zeroCell.X = 0;
	Renderer.zeroCell.Y = 0;

	return;
}

