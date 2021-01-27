// Parent Headers
#include "Game_LevelState_Ingame.h"



// Includes

#include "Game_EntryState.h"
#include "Game_LevelState_Paused.h"
#include "Game_Util.h"



BSS()

	StateObj Ingame_State;

	UI_Text Ingame_Text;

	UI_Text Ingame_GameOver_Fell;

	UI_Text Ingame_GameOver_MadeIt;

	Character Player;

	Level Level1;
	
	Level Level2_Why;

	sInt CurrentLevel = 1;

Data()

	bool ShouldReload = true;

	bool Ingame_DoneOnce = false;



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

fn returns(void) LevelState_Ingame_OnKeyUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Player.ShouldJump = true;

			break;
		}
		case EInput_Released:
		{
			break;
		}
	}
}

fn returns(void) LevelState_Ingame_OnKeyLeft parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Player.MoveState = ECharacter_MoveLeft;

			break;
		}
		case EInput_Released:
		{
			if (Player.MoveState == ECharacter_MoveLeft)
			{
				Player.MoveState = ECharacter_DontMove;
			}

			break;
		}
	}
}

fn returns(void) LevelState_Ingame_OnKeyRight parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Player.MoveState = ECharacter_MoveRight;

			break;
		}
		case EInput_Released:
		{
			if (Player.MoveState == ECharacter_MoveRight)
			{
				Player.MoveState = ECharacter_DontMove;
			}

			break;
		}
	}
}

fn returns(void) Load_Ingame parameters(void)
{
	if (! Ingame_DoneOnce)
	{
		Stack()
			COORD 
				start = { 1, 1 }, 
				end   = { 1, 1 } ;

		UI_Text_Create
		(
			getAddress(Ingame_Text),

			L"Press enter to pause.\0",
			start, end,
			false
		);

		start.X = 0; start.Y = 9;
		end  .X = 0; end  .Y = 9;
		
		UI_Text_Create
		(
			getAddress(Ingame_GameOver_Fell),

			L"Game Over: You fell\0",
			start, end,
			true
		);

		UI_Text_Create
		(
			getAddress(Ingame_GameOver_MadeIt),

			L"Game Over: You Made It!\0",
			start, end,
			true
		);

		// Level 1

		start.X = 0;                    start.Y = ERenderer_GameEnd - 1;
		end  .X = ERenderer_Width - 70; end  .Y = ERenderer_GameEnd - 1;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Ground);

		start.X = 0;                    start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 70; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Ground);

		start.X = ERenderer_Width - 70; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 60; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Pit);

		start.X = ERenderer_Width - 60; start.Y = ERenderer_GameEnd -1;
		end  .X = ERenderer_Width - 40; end  .Y = ERenderer_GameEnd -1;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Ground);

		start.X = ERenderer_Width - 60; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 40; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Ground);

		start.X = ERenderer_Width - 40; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 20; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Pit);

		start.X = ERenderer_Width - 20; start.Y = ERenderer_GameEnd - 1;
		end  .X = ERenderer_Width;      end  .Y = ERenderer_GameEnd - 1;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Ground);

		start.X = ERenderer_Width - 20; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width;      end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level1), start, end, LevelCell_Ground);

		// Level 2

		start.X = 0;                    start.Y = ERenderer_GameEnd - 1;
		end  .X = ERenderer_Width - 40; end  .Y = ERenderer_GameEnd - 1;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Ground);

		start.X = 0;                    start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 40; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Ground);

	 	start.X = ERenderer_Width - 40; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 25; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Pit);

		start.X = ERenderer_Width - 25; start.Y = ERenderer_GameEnd -1;
		end  .X = ERenderer_Width - 20; end  .Y = ERenderer_GameEnd -1;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Ground);

		start.X = ERenderer_Width - 25; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 20; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Ground);
	 
		start.X = ERenderer_Width - 20; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 10; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Pit);

		start.X = ERenderer_Width - 10; start.Y = ERenderer_GameEnd - 1;
		end  .X = ERenderer_Width;      end  .Y = ERenderer_GameEnd - 1;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Finish);

		start.X = ERenderer_Width - 10; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width;      end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(Level2_Why), start, end, LevelCell_Finish);


		Ingame_DoneOnce = true;
	}

	if (ShouldReload == true)
	{
		Character_Load(getAddress(Player));

		CurrentLevel = 1;

		ShouldReload = false;
	}

	Input_SubscribeTo(Key_Enter      , getAddress(LevelState_Ingame_OnKeyEnter));
	Input_SubscribeTo(Key_Arrow_Up   , getAddress(LevelState_Ingame_OnKeyUp   ));
	Input_SubscribeTo(Key_Arrow_Left , getAddress(LevelState_Ingame_OnKeyLeft ));
	Input_SubscribeTo(Key_Arrow_Right, getAddress(LevelState_Ingame_OnKeyRight));
}

fn returns(void) Unload_Ingame parameters(void)
{
	Input_Unsubscribe(Key_Enter      , getAddress(LevelState_Ingame_OnKeyEnter));
	Input_Unsubscribe(Key_Arrow_Up   , getAddress(LevelState_Ingame_OnKeyUp   ));
	Input_Unsubscribe(Key_Arrow_Left , getAddress(LevelState_Ingame_OnKeyLeft ));
	Input_Unsubscribe(Key_Arrow_Right, getAddress(LevelState_Ingame_OnKeyRight));
}

fn returns(void) Update_Ingame parameters(void)
{
	if (CurrentLevel == 2 && ! Character_AtFinish(getAddress(Player), getAddress(Level2_Why)))
	{
		Character_Update(getAddress(Player), getAddress(Level2_Why));	
	}

	if (CurrentLevel == 1)
	{
		Character_Update(getAddress(Player), getAddress(Level1));
	}

	if (CurrentLevel == 1 && Player.Position.X >= 0.98f)
	{
		CurrentLevel = 2;

		Player.Position.X = -0.975f; 
	}
}

fn returns(void) Render_Ingame parameters(void)
{
	if (CurrentLevel == 1)
	{
		Level_Render(getAddress(Level1));
	}
	else
	{
		Level_Render(getAddress(Level2_Why));
	}

	UI_Text_Render(getAddress(Ingame_Text));

	Character_Render(getAddress(Player));	

	if (Player.Fell)
	{
		UI_Text_Render(getAddress(Ingame_GameOver_Fell));
	}

	if (CurrentLevel == 2 && Character_AtFinish(getAddress(Player), getAddress(Level2_Why)))
	{
		UI_Text_Render(getAddress(Ingame_GameOver_MadeIt));
	}
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

fn returns(void) Ingame_Reload parameters(void)
{
	ShouldReload = true;
}

