// Parent Headers
#include "Game_LevelState_Ingame.h"



// Includes

#include "Game_LevelState_Paused.h"
#include "Game_Util.h"



BSS()

	StateObj Ingame_State;

Data()

	bool Ingame_DoneOnce = false;

	// Title

	CTS_CWString Ingame_Text = L"In-game";

	DataSize Ingame_Text_Length = 0;

	Ptr(Cell) Ingame_RenderCells = NULL;



// Functions

// Class Public

fn returns(void) LevelState_Ingame_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			LevelState_SetSubstate(GetPausedState());

			break;
		}
	}
}

fn returns(void) Load_Ingame parameters(void)
{
	if (! Ingame_DoneOnce)
	{
		Ingame_Text_Length = wcslen(Ingame_Text) + 1;

		Ingame_RenderCells = GlobalAllocate(Cell, Ingame_Text_Length);

		for (DataSize cellIndex = 0; cellIndex < Ingame_Text_Length; cellIndex++)
		{
			Ingame_RenderCells[cellIndex].Char.UnicodeChar = Ingame_Text[cellIndex];
		}

		Ingame_DoneOnce = true;
	}

	ChangeCellsTo_White(Ingame_RenderCells, Ingame_Text_Length);

	Input_SubscribeTo(Key_Enter, getAddress(LevelState_Ingame_OnKeyEnter));
}

fn returns(void) Unload_Ingame parameters(void)
{
	Input_Unsubscribe(Key_Enter, getAddress(LevelState_Ingame_OnKeyEnter));

	ChangeCellsTo_Grey(Ingame_RenderCells, Ingame_Text_Length);
}

fn returns(void) Update_Ingame parameters(void)
{
}

fn returns(void) Render_Ingame parameters(void)
{
	Stack()
		unbound COORD startingCell, endingCell;

	// In-game

	startingCell.X = 1;
	endingCell  .X = 1 + Ingame_Text_Length;

	startingCell.Y = 1;
	endingCell  .Y = 1;

	Renderer_WriteToBufferCells(Ingame_RenderCells, startingCell, endingCell);
}



// Public

fn returns( Ptr(StateObj)) GetIngameState parameters(void)
{
	unbound bool stateConstructed = false;

	if (!stateConstructed)
	{
		Ingame_State.Load   = getAddress(Load_Ingame  );
		Ingame_State.Unload = getAddress(Unload_Ingame);
		Ingame_State.Update = getAddress(Update_Ingame);
		Ingame_State.Render = getAddress(Render_Ingame);

		stateConstructed = true;
	}

	return getAddress(Ingame_State);
}

