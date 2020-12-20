// Parent Header
#include "Execution.h"



// Includes

#include "C_STL.h"
#include "CString.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"
#include "Renderer.h"



// Functions

fn returns(void) PrepareModules parameters(void)
{
	Cycler_LoadModule  ();
	CString_LoadModule ();
	Timing_LoadModule  ();
	Input_LoadModule   ();
	Renderer_LoadModule();
}

fn returns(void) PrintStartMessage parameters(void)
{
	Stack()

		CTS_CString EntryMessage = "TBF C Engine\n\nVersion: Phase 5\0";

	// Print Start Message

	print(EntryMessage);
}

fn returns(void) UnloadModules parameters(void)
{
	Renderer_UnloadModule();
}

// Entry Point

fn returns(ExecFlags) EntryPoint parameters(void)
{
	// Allocate our data array.

	//Heap(Data_Alloc());

	// Setup engine components.

	PrepareModules();

	PrintStartMessage();	

	// Core Engine Loop

	Cycler_Initialize();
	
	// Exit Engine

	printf("Exiting Game Engine: Press enter key to continue.");

	getchar();

	// Now that were done before we leave we deallocate the data array.

	//Heap(Data_Dealloc());

	UnloadModules();

	GlobalDeallocate();

	return ExecFlags_Sucess;
}
