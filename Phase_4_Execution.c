// Includes

#include "C_STL.h"
#include "LAL.h"
#include "Memory.h"



// Aliases (Typedefs)

alias(enum ExecFlags_Def) as ExecFlags;



// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Sucess = 0,
};




fn returns(void) Test_ScopedAllocations parameters(void) SmartScope
{
	Ptr(bool ) testBool   = ScopedAllocate(bool , 1);
	Ptr(char ) testChar   = StaticAllocate(char , 1); 
	Ptr(float) testFloats = ScopedAllocate(float, 2);

	val(testBool) = false;

	val(testChar) = 'a';

	testFloats[0] = 1.1F;
	testFloats[1] = 2.2F;
}
SmartScope_End





// SmartScope_End


// Entry Point

fn returns(ExecFlags) EntryPoint parameters(void)
{
	// Global Dynamic Allocation Test

	Ptr(int) testInt = StaticAllocate(int, 1);

	Test_ScopedAllocations();

	val(testInt) = 4;

	StaticDeallocate();

	return ExecFlags_Sucess;
}
