// Parent Header
#include "Input.h"



// Includes
#include "Cycler.h"
#include "Memory.h"



// Static Data

// Private

BSS()

	InputData Input;



// Forward Declarations

fn returns(EKeyCode) GetKeyCodeAtIndex(DataSize _index);
fn returns(DataSize) GetKeyIndexFromCode(EKeyCode _key);



// Functions

// Public

fn returns(void) Input_LoadModule parameters(void)
{
	//Input.StateIndex = 0;
}

fn returns(ro Ptr(InputData)) Input_GetContext(void)
{
	return getAddress(Input);
}

fn returns(bool) Input_GetKeyTap(EKeyCode _key, DataSize _recordLength)
{
	Stack()

		DataSize 
			//queryIndex    = Input.Index_CurrentState, 
			relativeIndex = 0; 

		bool 
			foundRelease = false, 
			foundPress   = false ;

		Ptr(InputState_RingBuffer) ringBuffer = getAddress(Input.KeyStateBuffer[GetKeyIndexFromCode(_key)]);


	if (_recordLength > InputState_BufferSize)
	{
		for (; relativeIndex < InputState_BufferSize; relativeIndex++)
		{
			Stack()
				EInputState keyState = ringBuffer->Buffer[ringBuffer->Index - relativeIndex];

			if (keyState == EInput_Released)
			{
				foundRelease = true;
			}

			if (foundRelease && keyState == EInput_Pressed)
			{
				foundPress = true;
			}
		}
	}
	else
	{
		for (; relativeIndex < _recordLength; relativeIndex++)
		{
			Stack()
				EInputState keyState = ringBuffer->Buffer[ringBuffer->Index - relativeIndex];

			if (keyState == EInput_Released)
			{
				foundRelease = true;
			}

			if (foundRelease && keyState == EInput_Pressed)
			{
				foundPress = true;
			}
		}
	}

	return foundPress && foundRelease;
}

fn returns(void) Input_Update parameters(void)
{
	DataSize index = 0; 

	for (; index < Keys_NumTracked; index++)
	{
		Stack()
			bool Current, Previous;

		// Get current signal state

		Input.PreviousSignalState.Array[index] = Input.CurrentSignalState.Array[index];

		Previous = Input.CurrentSignalState.Array[index];

		Input.CurrentSignalState.Array[index] = GetKeySignal(GetKeyCodeAtIndex(index));

		Current = Input.CurrentSignalState.Array[index];

		// Determine latest key state.

		Stack() EInputState latestState;

		if (Current == Previous)
		{
			if (Current == true)
			{
				latestState = EInput_Held;
			}
			else
			{
				latestState = EInput_None;
			}
		}
		else
		{
			if (Current == false)
			{
				latestState = EInput_Released;
			}
			else
			{
				latestState = EInput_Pressed;
			}
		}

		Ptr(InputState_RingBuffer) ringBuffer = getAddress(Input.KeyStateBuffer[index]);

		Stack() EInputState CurrentState = ringBuffer->Buffer[ringBuffer->Index];

		if (latestState != CurrentState)
		{
			if (CurrentState >= (InputState_BufferSize - 1))
			{
				ringBuffer->Index = 0;
			}
			else
			{
				ringBuffer->Index = ringBuffer->Index + 1;
			}

			ringBuffer->Buffer[ringBuffer->Index] = latestState;

			switch (latestState)
			{
				case EInput_Held:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: Held");

					break;
				}
				case EInput_None:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: None");

					break;
				}
				case EInput_Released:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: Released");

					break;
				}
				case EInput_Pressed:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: Pressed");

					break;
				}
			}
		}
	}
}



// Private

fn returns(EKeyCode) GetKeyCodeAtIndex(DataSize _index)
{
	switch (_index)
	{
		case 0:
		{
			return Key_Arrow_UP;
		}
		case 1:
		{
			return Key_Arrow_Down;
		}
		case 2:
		{
			return Key_Arrow_Left;
		}
		case 3:
		{
			return Key_Arrow_Right;
		}
	}
}

fn returns(DataSize) GetKeyIndexFromCode(EKeyCode _key)
{
	switch (_key)
	{
		case Key_Arrow_UP:
		{
			return 0;
		}
		case Key_Arrow_Down:
		{
			return 1;
		}
		case Key_Arrow_Left:
		{
			return 2;
		}
		case Key_Arrow_Right:
		{
			return 3;
		}
	}
}
