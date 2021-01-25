// Parent Header
#include "Game_LevelState_Paused.h"



// Includes

#include "Game_LevelState_Ingame.h"
#include "Game_Util.h"



BSS()

	StateObj Paused_State;

	UI_Widget PauseWidget;

Data()

	bool Paused_DoneOnce = false;

	uInt PauseUI_Index = 0;

	// Title

	CTS_CWString PauseTitle_Text = L"Paused";

	DataSize PauseTitle_Text_Length = 0;

	Ptr(Cell) PauseTitle_RenderCells = NULL;

	// Resume button

	CTS_CWString Resume_Text = L"Resume";

	DataSize Resume_Text_Length = 0;

	Ptr(Cell) Reusme_RenderCells = NULL;

	// Quit to Menu button

	CTS_CWString QuitToMenu_Text = L"Quit to Menu";

	DataSize QuitToMenu_Text_Length = 0;

	Ptr(Cell) QuitToMenu_RenderCells = NULL;



// Enums

enum
{
	EUI_Resume     = 0,
	EUI_QuitToMenu = 1
};



// Functions

// Class Public

fn returns(void) Level_State_Paused_PressResume parameters(void)
{
	LevelState_SetSubstate(GetIngameState());
}

fn returns(void) Level_State_Paused_PressQuitToMenu parameters(void)
{
	State_SetState(LoadGame());
}

fn returns(void) LevelState_Paused_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			UI_Widget_Select(getAddress(PauseWidget));

			break;
		}
	}
}

fn returns(void) LevelState_Paused_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"Pause: On Key Up");

			UI_Widget_MoveUp(getAddress(PauseWidget));

			break;
		}
	}
}

fn returns(void) LevelState_Paused_OnKeyArrowDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"Pause: On Key Down");

			UI_Widget_MoveDown(getAddress(PauseWidget));

			break;
		}
	}
}

fn returns(void) Load_Paused parameters(void)
{
	PauseUI_Index = 0;

	if (! Paused_DoneOnce)
	{
		PauseWidget.TextUIs           = NULL;
		PauseWidget.Num_TextUIs       = 0;
		PauseWidget.Grid.Buttons      = NULL;
		PauseWidget.Grid.Num          = 0;
		PauseWidget.Grid.CurrentIndex = 0;

		Stack() 

			COORD startCell, endCell;

		startCell.X = 0; endCell.X = 0;
		startCell.Y = 9; endCell.Y = 9;

		UI_Widget_AddText
		(
			getAddress(PauseWidget),

			L"Paused\0",
			startCell, 
			endCell,
			true   // Should Center
		);

		startCell.Y = 15; endCell.Y = 15;

		UI_Widget_AddButton
		(
			getAddress(PauseWidget),

			L"Resume\0",
			startCell, endCell,
			true,
			getAddress(Level_State_Paused_PressResume)
		);

		startCell.X = 0; endCell.X = 0;
		startCell.Y = 17; endCell.Y = 17;

		UI_Widget_AddButton
		(
			getAddress(PauseWidget),

			L"Quit to Menu\0",
			startCell, endCell,
			true,
			getAddress(Level_State_Paused_PressQuitToMenu)
		);

		Paused_DoneOnce = true;
	}

	Input_SubscribeTo(Key_Enter     , getAddress(LevelState_Paused_OnKeyEnter    ));
	Input_SubscribeTo(Key_Arrow_Up  , getAddress(LevelState_Paused_OnKeyArrowUp  ));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(LevelState_Paused_OnKeyArrowDown));
}

fn returns(void) Unload_Paused parameters(void)
{
	Input_Unsubscribe(Key_Enter     , getAddress(LevelState_Paused_OnKeyEnter    ));
	Input_Unsubscribe(Key_Arrow_Up  , getAddress(LevelState_Paused_OnKeyArrowUp  ));
	Input_Unsubscribe(Key_Arrow_Down, getAddress(LevelState_Paused_OnKeyArrowDown));
}

fn returns(void) Update_Paused parameters(void)
{
}

fn returns(void) Render_Paused parameters(void)
{
	UI_Widget_Render(getAddress(PauseWidget));
}



// Public

fn returns(Ptr(StateObj)) GetPausedState parameters(void)
{
	unbound bool stateConstructed = false;

	if (!stateConstructed)
	{
		Paused_State.Load   = getAddress(Load_Paused  );
		Paused_State.Unload = getAddress(Unload_Paused);
		Paused_State.Update = getAddress(Update_Paused);
		Paused_State.Render = getAddress(Render_Paused);

		stateConstructed = true;
	}

	return getAddress(Paused_State);
}
