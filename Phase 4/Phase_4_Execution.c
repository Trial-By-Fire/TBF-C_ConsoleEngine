// Includes

#include <stdlib.h>

// Trial By Fire

//#include "Core.h"
#include "fundamentalTypes.h"
#include "Memory.h"



fn returns(void) Test parameters(void) SmartScope
{
	Ptr(bool) testBool = ScopedAllocate(bool, 1);

	val(testBool) = false;

	Ptr(char) testChar = StaticAllocate(bool, 1);

	val(testChar) = 'a';

	Ptr(float) testFloats = ScopedAllocate(float, 2);

	testFloats[0] = 1.1F;
	testFloats[1] = 2.2F;
}
SmartScope_End



fn returns(ExecFlags) EntryPoint parameters(void)
{
	Ptr(int) testInt = StaticAllocate(int, 1);

	//Launch_V3();

	Test();

	val(testInt) = 4;

	StaticDeallocate();

	return ExecFlags_Success;
}
