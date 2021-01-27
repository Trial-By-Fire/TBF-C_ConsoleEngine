// Parent Header
#include "Execution.h"



// Includes

#include "C_STL.h"
#include "CString.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"
#include "Renderer.h"
#include "State.h"



// Functions

fn returns(void) PrepareModules parameters(void)
{
	Cycler_LoadModule  ();
	CString_LoadModule ();
	Timing_LoadModule  ();
	Input_LoadModule   ();
	Renderer_LoadModule();
	State_LoadModule   ();
}

fn returns(void) PrintStartMessage parameters(void)
{
	Renderer_WriteToLog(L"TBF C Engine");

	Renderer_WriteToLog(L"");

	Renderer_WriteToLog(L"Version: Phase 8");
}

fn returns(void) UnloadModules parameters(void)
{
	Renderer_UnloadModule();
}

// Entry Point

fn returns(ExecFlags) EntryPoint parameters(void)
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
