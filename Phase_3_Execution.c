// Includes

#include "C_STL.h"
#include "LAL.h"
#include "CString.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"
#include "Renderer.h"



// Aliases (Typedefs)

alias(enum ExecFlags_Def) as ExecFlags;



// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Sucess = 0,
};


fn returns(void) PrepareModules parameters(void)
{
	Cycler_LoadModule  ();
	CString_LoadModule ();
	Timing_LoadModule  ();
	Input_LoadModule   ();
	Renderer_LoadModule();
}


// Entry Point

fn returns(ExecFlags) EntryPoint parameters(void)
{
	// Allocate our data array.

	Heap(Data_Alloc());

	// Setup engine components.

	PrepareModules();

	CString_PrintStartMessage();	

	// Core Engine Loop

	Cycler_Initialize();
	
	// Exit Engine

	printf("Exiting Game Engine: Press enter key to continue.");

	getchar();

	// Now that were done before we leave we deallocate the data array.

	Heap(Data_Dealloc());

	return ExecFlags_Sucess;
}
