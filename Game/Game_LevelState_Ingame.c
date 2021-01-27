// Parent Headers
#include "Game_LevelState_Ingame.h"



// Includes

#include "Game_LevelState_Paused.h"
#include "Game_Util.h"



BSS()

	StateObj Ingame_State;

	UI_Text Ingame_Text;

	Character Player;

	Level TestLevel;

Data()

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

			L"In-game\0",
			start, end,
			false
		);

		Character_Load(getAddress(Player));

		start.X = 0;                    start.Y = ERenderer_GameEnd - 1;
		end  .X = ERenderer_Width - 30; end  .Y = ERenderer_GameEnd - 1;

		Level_SetCells(getAddress(TestLevel), start, end, LevelCell_Ground);

		start.X = 0;                    start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width - 30; end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(TestLevel), start, end, LevelCell_Ground);

		start.X = ERenderer_Width - 30; start.Y = ERenderer_GameEnd;
		end  .X = ERenderer_Width;      end  .Y = ERenderer_GameEnd;

		Level_SetCells(getAddress(TestLevel), start, end, LevelCell_Pit);


		Ingame_DoneOnce = true;
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
	Character_Update(getAddress(Player), getAddress(TestLevel));
}

fn returns(void) Render_Ingame parameters(void)
{
	Level_Render(getAddress(TestLevel));

	UI_Text_Render(getAddress(Ingame_Text));

	Character_Render(getAddress(Player));	
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

