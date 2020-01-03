// Includes

// C Stadnard Library

#include <stdlib.h>

// Trial By Fire

#include "fundamentalTypes.h"
#include "Memory.h"



fn returns(void) Test parameters(void) SmartScope
{
	Stack
	(
		Ptr(bool ) testBool   = Heap( ScopedAllocate(bool , 1) );
		Ptr(char ) testChar   = Heap( StaticAllocate(bool , 1) );
		Ptr(float) testFloats = Heap( ScopedAllocate(float, 2) );
	)

	val(testBool) = false;

	val(testChar) = 'a';

	testFloats[0] = 1.1F;
	testFloats[1] = 2.2F;
}
SmartScope_End



fn returns(ExecFlags) EntryPoint parameters(void)
{
	Stack
	(
		Ptr(int) testInt = Heap( StaticAllocate(int, 1) );
	)

	//Launch_V3();

	Test();

	val(testInt) = 4;

	Heap( StaticDeallocate() );

	return ExecFlags_Success;
}
