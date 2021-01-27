// Parent Header
#include "Game_LevelState_Paused.h"



// Includes

#include "Game_LevelState_Ingame.h"
#include "Game_Util.h"



BSS()

	StateObj Paused_State;

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

fn returns(void) LevelState_Paused_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			switch (PauseUI_Index)
			{
				case EUI_Resume:
				{
					LevelState_SetSubstate(GetIngameState());

					break;
				}
				case EUI_QuitToMenu:
				{
					State_SetState(LoadGame());

					break;
				}
			}

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

			if (PauseUI_Index == 1)
			{
				PauseUI_Index--;

				Renderer_WriteToLog(L"Pause UI Resume Active");

				ChangeCellsTo_White(Reusme_RenderCells    , Resume_Text_Length    );
				ChangeCellsTo_Grey (QuitToMenu_RenderCells, QuitToMenu_Text_Length);
			}

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

			if (PauseUI_Index == 0)
			{
				PauseUI_Index++;

				Renderer_WriteToLog(L"Pause UI Quit to Menu Active");

				ChangeCellsTo_Grey (Reusme_RenderCells    , Resume_Text_Length    );
				ChangeCellsTo_White(QuitToMenu_RenderCells, QuitToMenu_Text_Length);
			}

			break;
		}
	}
}

fn returns(void) Load_Paused parameters(void)
{
	PauseUI_Index = 0;

	if (! Paused_DoneOnce)
	{
		// Title

		PauseTitle_Text_Length = wcslen(PauseTitle_Text) + 1;

		PauseTitle_RenderCells = GlobalAllocate(Cell, PauseTitle_Text_Length);

		for (DataSize cellIndex = 0; cellIndex < PauseTitle_Text_Length; cellIndex++)
		{
			PauseTitle_RenderCells[cellIndex].Char.UnicodeChar = PauseTitle_Text[cellIndex];
		}

		// Resume button

		Resume_Text_Length = wcslen(Resume_Text) + 1;

		Reusme_RenderCells = GlobalAllocate(Cell, Resume_Text_Length);

		for (DataSize cellIndex = 0; cellIndex < Resume_Text_Length; cellIndex++)
		{
			Reusme_RenderCells[cellIndex].Char.UnicodeChar = Resume_Text[cellIndex];
		}

		// Quite to Menu button

		QuitToMenu_Text_Length = wcslen(QuitToMenu_Text) + 1;

		QuitToMenu_RenderCells = GlobalAllocate(Cell, QuitToMenu_Text_Length);

		for (DataSize cellIndex = 0; cellIndex < QuitToMenu_Text_Length; cellIndex++)
		{
			QuitToMenu_RenderCells[cellIndex].Char.UnicodeChar = QuitToMenu_Text[cellIndex];
		}

		Paused_DoneOnce = true;
	}

	ChangeCellsTo_White(PauseTitle_RenderCells, PauseTitle_Text_Length);
	ChangeCellsTo_White(Reusme_RenderCells    , Resume_Text_Length    );
	ChangeCellsTo_Grey (QuitToMenu_RenderCells, QuitToMenu_Text_Length);

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
	Stack()
		unbound COORD startingCell, endingCell;

	// Title

	startingCell.X = (ERenderer_Width / 2) - (PauseTitle_Text_Length / 2) - 1;
	endingCell  .X = (ERenderer_Width / 2) + (PauseTitle_Text_Length / 2) - 1;

	startingCell.Y = 9;
	endingCell  .Y = 9;

	Renderer_WriteToBufferCells(PauseTitle_RenderCells, startingCell, endingCell);

	// Resume button cell

	startingCell.X = (ERenderer_Width / 2) - (Resume_Text_Length / 2) - 1;
	endingCell  .X = (ERenderer_Width / 2) + (Resume_Text_Length / 2) - 1;

	startingCell.Y = 15;
	endingCell  .Y = 15;

	Renderer_WriteToBufferCells(Reusme_RenderCells, startingCell, endingCell);

	// Quit to Menu cells

	startingCell.X = (ERenderer_Width / 2) - (QuitToMenu_Text_Length / 2) - 1;
	endingCell  .X = (ERenderer_Width / 2) + (QuitToMenu_Text_Length / 2) - 1;

	startingCell.Y = 17;
	endingCell  .Y = 17;

	Renderer_WriteToBufferCells(QuitToMenu_RenderCells, startingCell, endingCell);
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
