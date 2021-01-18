#pragma once



// Windows Library

#include <conio.h>
#include <Windows.h>



#include "LAL.h"




// Macros

#define Console_Cursor_MinSize 1

#define Console_Cursor_NotVisible 0


#define Console_WhiteCell \
FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY


// Aliases (Typedefs)


// Forward Declarations

fn returns(bool) Bind_IOBufferTo_Console parameters(void);

fn returns(bool) RequestConsole parameters(void);

fn returns(bool) Unbind_IOBufferTo_Console parameters(void);
