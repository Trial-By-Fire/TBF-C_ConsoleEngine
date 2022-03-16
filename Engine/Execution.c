// Parent Header
#include "Execution.h"



// Includes

#include "C_STL.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"
#include "Renderer.h"
#include "State.h"



// Functions

void PrepareModules(void) 
{
	Cycler_LoadModule  ();
	Timing_LoadModule  ();
	Input_LoadModule   ();
	Renderer_LoadModule();
	State_LoadModule   ();
}

void PrintStartMessage(void)
{
	Renderer_WriteToLog(L"TBF C Engine");

	Renderer_WriteToLog(L"");

	Renderer_WriteToLog(L"Version: Phase 14");
}

void UnloadModules(void)
{
	Renderer_UnloadModule();
}

// Entry Point

ExecFlags EntryPoint(void)
{
	// Setup engine components.

	PrepareModules();

	PrintStartMessage();	

	// Core Engine Loop

	Cycler_Initialize();
	
	UnloadModules();

	GlobalDeallocate();

	return ExecFlags_Sucess;
}
