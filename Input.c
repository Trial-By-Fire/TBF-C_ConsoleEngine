// Parent Header
#include "Input.h"



// Includes
#include "Cycler.h"
#include "Memory.h"



// Static Data

// Private

BSS()

	InputData Input;

	char LastKeyPressed;



// Functions

// Public

fn returns(void) Input_LoadModule parameters(void)
{
	Input.LastPressedKey = '\0';
}

fn returns(ro Ptr(InputData)) Input_GetContext(void)
{
	return getAddress(Input);
}

fn returns(Key) Input_GetKeyPress parameters(void)
{
	return (Key)_getch();
}

fn returns(bool) Input_KeyboardHit parameters(void)
{
	return (bool)_kbhit();
}

fn returns(void) Input_Update parameters(void)
{
	if (Input_KeyboardHit())
	{
		Input.LastPressedKey = Input_GetKeyPress();
	}

	if (Input.LastPressedKey == 'q')
	{
		Cycler_Lapse();	
	}
}
