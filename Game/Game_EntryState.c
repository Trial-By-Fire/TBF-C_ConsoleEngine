// Parent Header
#include "Game_EntryState.h"



// Include

#include "Game_LevelState.h"
#include "Game_Util.h"



BSS()

	StateObj MainMenu;

	UI_Widget MenuWidget;

Data()

	bool Menu_DoneOnce = false;

	bool 
		Log_Load   = true;
		Log_Unload = true;



// Functions

// Public Class

fn returns(void) MainMenu_PressStart parameters(void)
{
	Renderer_WriteToLog(L"UI Start Selected");

	State_SetState(GetLevelState());
}

fn returns(void) MainMenu_PressQuit parameters(void)
{
	Cycler_Quit();
}

fn returns(void) Game_EntryState_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Up");

			UI_Widget_MoveUp(getAddress(MenuWidget));

			break;
		}
	}
}

fn returns(void) Game_EntryState_OnKeyArrowDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Down");

			UI_Widget_MoveDown(getAddress(MenuWidget));

			break;
		}
	}
}

fn returns(void) Game_EntryState_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Enter");

			UI_Widget_Select(getAddress(MenuWidget));

			break;
		}
	}
}

fn returns(void) MainMenu_Load parameters(void)
{
	if (! Menu_DoneOnce)
	{
		MenuWidget.TextUIs           = NULL;
		MenuWidget.Num_TextUIs       = 0;
		MenuWidget.Grid.Buttons      = NULL;
		MenuWidget.Grid.Num          = 0;
		MenuWidget.Grid.CurrentIndex = 0;

		Stack() 

			COORD startCell, endCell;

		startCell.X = 0; endCell.X = 0;
		startCell.Y = 9; endCell.Y = 9;



		UI_Widget_AddText
		(
			getAddress(MenuWidget),

			L"Generic Platformer Demo\0",
			startCell, 
			endCell,
			true   // Should Center
		);

		startCell.Y = 15; endCell.Y = 15;

		UI_Widget_AddButton
		(
			getAddress(MenuWidget),

			L"Start\0",
			startCell, endCell,
			true,
			getAddress(MainMenu_PressStart)
		);

		startCell.X = -1; endCell.X = -1;
		startCell.Y = 17; endCell.Y = 17;

		UI_Widget_AddButton
		(
			getAddress(MenuWidget),

			L"Quit\0",
			startCell, endCell,
			true,
			getAddress(MainMenu_PressQuit)
		);

		Menu_DoneOnce = true;
	}

	Input_SubscribeTo(Key_Arrow_Up  , getAddress(Game_EntryState_OnKeyArrowUp  ));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(Game_EntryState_OnKeyArrowDown));
	Input_SubscribeTo(Key_Enter     , getAddress(Game_EntryState_OnKeyEnter    ));

	if (Log_Load)
	{
		Renderer_WriteToLog(L"Loaded: Main Menu");

		Log_Load = false;
	}
}

fn returns(void) MainMenu_Unload parameters(void)
{
	Input_Unsubscribe(Key_Arrow_Up  , getAddress(Game_EntryState_OnKeyArrowUp  ));
	Input_Unsubscribe(Key_Arrow_Down, getAddress(Game_EntryState_OnKeyArrowDown));
	Input_Unsubscribe(Key_Enter     , getAddress(Game_EntryState_OnKeyEnter    ));

	if (Log_Unload)
	{
		Renderer_WriteToLog(L"Unload: Main Menu");

		Log_Unload = false;
	}
}

fn returns(void) MainMenu_Update parameters(void)
{
}

fn returns(void) MainMenu_Render parameters(void)
{
	UI_Widget_Render(getAddress(MenuWidget));
}



// Engine Entrypoint

fn returns(Ptr(StateObj)) LoadGame parameters(void)
{
	unbound bool stateConstructed = false;

	if (! stateConstructed)
	{
		MainMenu.Load   = getAddress(MainMenu_Load  );
		MainMenu.Unload = getAddress(MainMenu_Unload);
		MainMenu.Update = getAddress(MainMenu_Update);
		MainMenu.Render = getAddress(MainMenu_Render);

		stateConstructed = true;
	}

	return getAddress(MainMenu);
}



