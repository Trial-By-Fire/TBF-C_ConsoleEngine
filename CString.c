// Parent Header
#include "CString.h"



// Includes
#include "Memory.h"



// Static Data

// Private

// Static Data

BSS
(
	Ptr(CString) Message_HelloWorld; 
)


// Functions

// Public

fn returns(void) CString_PrintStartMessage parameters(void)
{
	// Print Start Message

	print(Message_HelloWorld->Array);
}

fn returns(void) CString_LoadModule parameters(void)
{
	Message_HelloWorld = Data_AssignMemory(SizeOf_CString);

	SetupStartMessage();
}

fn returns(void) SetupStartMessage parameters(void)
{
	Message_HelloWorld->Length = SizeOf_HelloWorld;

	Message_HelloWorld->Array = Heap(AllocateMemory(Message_HelloWorld->Length));

	// Setup the values of the message string. 

	Message_HelloWorld->Array[0] = 'H';   // val( (Message + 0) ) = 'H';
	Message_HelloWorld->Array[1] = 'e';
	Message_HelloWorld->Array[2] = 'l';
	Message_HelloWorld->Array[3] = 'l';
	Message_HelloWorld->Array[4] = 'o';
	Message_HelloWorld->Array[5] = ' ';
	Message_HelloWorld->Array[6] = 'W';
	Message_HelloWorld->Array[7] = 'o';
	Message_HelloWorld->Array[8] = 'r';
	Message_HelloWorld->Array[9] = 'l';
	Message_HelloWorld->Array[10] = 'd';
	Message_HelloWorld->Array[11] = '!';
	Message_HelloWorld->Array[12] = '\0';

	// Once we have the values we print the message.

	return;
}
