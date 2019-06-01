// Parent Header
#include "Input.h"



// Includes

// C Standard Library

#include <stdbool.h>

// Windows

#include <conio.h>



// Functions

fn returns(bool) KeyboardHit parameters(void)
{
	return _kbhit();
}

fn returns(int) GetKeyPress parameters(void)
{
	return _getch();
}
