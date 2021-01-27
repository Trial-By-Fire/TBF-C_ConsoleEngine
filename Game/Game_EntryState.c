// Parent Header
#include "Game_EntryState.h"



// Include

#include "Game_LevelState.h"
#include "Game_Util.h"



BSS()

	StateObj MainMenu;

Data()

	bool Menu_DoneOnce = false;

	bool 
		Log_Load   = true;
		Log_Unload = true;

	// UI

	DataSize UI_Index = 1;

	enum 
	{
		EUI_None  = 0,
		EUI_Start = 1,
		EUI_Quit  = 2
	};

	// Title

	CTS_CWString MainTitle_Text = L"Generic Platform Demo";

	DataSize MainTitle_Text_Length = 0;

	Ptr(Cell) MainTitle_RenderCells = NULL;

	// Start Button

	CTS_CWString Start_Text = L"Start";

	DataSize Start_Text_Length = 0;

	Ptr(Cell) Start_RenderCells = NULL;

	sInt16 Start_X = -1;

	bool Start_Nudgged = false;

	TimerData Start_NudgeTime;

	// Quit Button

	CTS_CWString Quit_Text = L"Quit";

	DataSize Quit_Text_Length = 0;

	Ptr(Cell) Quit_RenderCells = NULL;



// Functions

// Private

fn returns(void) Quit_SetTextTo_Grey parameters(void)
{
	for (DataSize cellIndex = 0; cellIndex < Quit_Text_Length; cellIndex++)
	{
		Quit_RenderCells[cellIndex].Attributes = FOREGROUND_INTENSITY;
	}
}

fn returns(void) Quit_SetTextTo_White parameters(void)
{
	for (DataSize cellIndex = 0; cellIndex < Quit_Text_Length; cellIndex++)
	{
		Quit_RenderCells[cellIndex].Attributes = Console_WhiteCell;
	}
}


// Public Class

fn returns(void) Game_EntryState_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Up");

			if (UI_Index == 2)
			{
				UI_Index--;

				Renderer_WriteToLog(L"UI Start Active");

				ChangeCellsTo_White(Start_RenderCells, Start_Text_Length);
				ChangeCellsTo_Grey (Quit_RenderCells , Quit_Text_Length );
			}

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

			if (UI_Index == 1)
			{
				UI_Index++;

				Renderer_WriteToLog(L"UI Quit Active");

				ChangeCellsTo_Grey (Start_RenderCells, Start_Text_Length);
				ChangeCellsTo_White(Quit_RenderCells , Quit_Text_Length );
			}

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

			switch (UI_Index)
			{
				case EUI_Start:
				{
					Renderer_WriteToLog(L"UI Start Selected");

					State_SetState(GetLevelState());

					//Start_X++;

					//Start_Nudgged = true;

					break;
				}
				case EUI_Quit:
				{
					Cycler_Quit();

					break;
				}
			}

			break;
		}
	}
}

fn returns(void) MainMenu_Load parameters(void)
{
	if (! Menu_DoneOnce)
	{
		MainTitle_Text_Length = wcslen(MainTitle_Text) + 1;
		Start_Text_Length     = wcslen(Start_Text    ) + 1;
		Quit_Text_Length      = wcslen(Quit_Text     )    ;

		MainTitle_RenderCells = GlobalAllocate(Cell, MainTitle_Text_Length);
		Start_RenderCells     = GlobalAllocate(Cell, Start_Text_Length    );
		Quit_RenderCells      = GlobalAllocate(Cell, Quit_Text_Length     );

		for (DataSize cellIndex = 0; cellIndex < MainTitle_Text_Length; cellIndex++)
		{
			MainTitle_RenderCells[cellIndex].Char.UnicodeChar = MainTitle_Text[cellIndex];
		}

		for (DataSize cellIndex = 0; cellIndex < Start_Text_Length; cellIndex++)
		{
			Start_RenderCells[cellIndex].Char.UnicodeChar = Start_Text[cellIndex];
		}

		for (DataSize cellIndex = 0; cellIndex < Quit_Text_Length; cellIndex++)
		{
			Quit_RenderCells[cellIndex].Char.UnicodeChar = Quit_Text[cellIndex];
		}

		Start_NudgeTime.EndTime = 0.075L;

		Menu_DoneOnce = true;
	}

	ChangeCellsTo_White(MainTitle_RenderCells, MainTitle_Text_Length);
	ChangeCellsTo_White(Start_RenderCells    , Start_Text_Length    );
	ChangeCellsTo_Grey (Quit_RenderCells     , Quit_Text_Length     );

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
	if (Start_Nudgged)
	{
		Timer_Tick(getAddress(Start_NudgeTime));

		if (Timer_Ended(getAddress(Start_NudgeTime)))
		{
			Start_X--;

			Start_Nudgged = false;

			Timer_Reset(getAddress(Start_NudgeTime));
		}
	}
}

fn returns(void) MainMenu_Render parameters(void)
{
	Stack()
		unbound COORD
		startingCell = { 0, 15 },
		endingCell   = { 0, 15 };

	// Title Cells

	startingCell.X = (ERenderer_Width / 2) - (MainTitle_Text_Length / 2) - 1;
	endingCell  .X = (ERenderer_Width / 2) + (MainTitle_Text_Length / 2) - 1;

	startingCell.Y = 9;
	endingCell  .Y = 9;

	Renderer_WriteToBufferCells(MainTitle_RenderCells, startingCell, endingCell);

	// Start UI Cells

	startingCell.X = (ERenderer_Width / 2) - (Start_Text_Length / 2)  + Start_X;
	endingCell  .X = (ERenderer_Width / 2) + (Start_Text_Length / 2)  + Start_X;

	startingCell.Y = 15;
	endingCell  .Y = 15;

	Renderer_WriteToBufferCells(Start_RenderCells, startingCell, endingCell);

	// Quit UI Cells

	startingCell.X = (ERenderer_Width / 2) - (Quit_Text_Length / 2) - 2;
	endingCell  .X = (ERenderer_Width / 2) + (Quit_Text_Length / 2) - 2;

	startingCell.Y = 17;
	endingCell  .Y = 17;

	Renderer_WriteToBufferCells(Quit_RenderCells, startingCell, endingCell);
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



