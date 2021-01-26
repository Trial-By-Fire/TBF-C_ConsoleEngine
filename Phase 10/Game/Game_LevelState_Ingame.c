// Parent Headers
#include "Game_LevelState_Ingame.h"



// Includes

#include "Game_LevelState_Paused.h"
#include "Game_Util.h"



enum 
	{
		EDontMove,
		EMove_Up,
		EMove_Down,
		EMove_Left,
		EMove_Right
	};



BSS()

	StateObj Ingame_State;

	UI_Text Ingame_Text;

	Cell Char_Sprite;

	COORD CharSprite_RenderCoord;

	Vector2D Char_Position;

Data()

	bool Ingame_DoneOnce = false;

	sInt MoveState =EDontMove;



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
			MoveState = EMove_Up;

			break;
		}
		case EInput_Released:
		{
			if (MoveState == EMove_Up)
			{
				MoveState = EDontMove;
			}

			break;
		}
	}
}

fn returns(void) LevelState_Ingame_OnKeyDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			MoveState = EMove_Down;

			break;
		}
		case EInput_Released:
		{
			if (MoveState == EMove_Down)
			{
				MoveState = EDontMove;
			}

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
			MoveState = EMove_Left;	

			break;
		}
		case EInput_Released:
		{
			if (MoveState == EMove_Left)
			{
				MoveState = EDontMove;
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
			MoveState = EMove_Right;	

			break;
		}
		case EInput_Released:
		{
			if (MoveState == EMove_Right)
			{
				MoveState = EDontMove;
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


		Char_Sprite.Char.UnicodeChar = 0;
		Char_Sprite.Attributes       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

		CharSprite_RenderCoord.X = 0;
		CharSprite_RenderCoord.Y = 0;

		Char_Position.X = 0.0f;
		Char_Position.Y = 0.0f;


		Ingame_DoneOnce = true;
	}

	Input_SubscribeTo(Key_Enter      , getAddress(LevelState_Ingame_OnKeyEnter));
	Input_SubscribeTo(Key_Arrow_Up   , getAddress(LevelState_Ingame_OnKeyUp   ));
	Input_SubscribeTo(Key_Arrow_Down , getAddress(LevelState_Ingame_OnKeyDown ));
	Input_SubscribeTo(Key_Arrow_Left , getAddress(LevelState_Ingame_OnKeyLeft ));
	Input_SubscribeTo(Key_Arrow_Right, getAddress(LevelState_Ingame_OnKeyRight));
}

fn returns(void) Unload_Ingame parameters(void)
{
	Input_Unsubscribe(Key_Enter      , getAddress(LevelState_Ingame_OnKeyEnter));
	Input_Unsubscribe(Key_Arrow_Up   , getAddress(LevelState_Ingame_OnKeyUp   ));
	Input_Unsubscribe(Key_Arrow_Left , getAddress(LevelState_Ingame_OnKeyDown ));
	Input_Unsubscribe(Key_Arrow_Left , getAddress(LevelState_Ingame_OnKeyLeft ));
	Input_Unsubscribe(Key_Arrow_Right, getAddress(LevelState_Ingame_OnKeyRight));
}

fn returns(void) Update_Ingame parameters(void)
{
	Stack()
		float32 deltaTime = (float32)Timing_GetContext()->DeltaTime;

		unbound float32 velocity = 1.0f;

	switch (MoveState)
	{
		case EMove_Up:
		{
			if (Char_Position.Y < 1.0f)
			{
				Char_Position.Y += velocity * deltaTime;
			}

			break;
		}
		case EMove_Down:
		{
			if (Char_Position.Y > -1.0f)
			{
				Char_Position.Y -= velocity * deltaTime;
			}

			break;
		}
		case EMove_Left:
		{
			if (Char_Position.X > -1.0f)
			{
				Char_Position.X -= velocity * deltaTime;
			}

			break;
		}
		case EMove_Right:
		{
			if (Char_Position.X < 1.0f)
			{
				Char_Position.X += velocity * deltaTime;
			}

			break;
		}
	}
}

fn returns(void) Render_Ingame parameters(void)
{
	UI_Text_Render(getAddress(Ingame_Text));

	CharSprite_RenderCoord = Convert_Vector2D_ToRenderCoord(Char_Position);

	Renderer_WriteToPersistentSection(1, L"Pos X: %f", Char_Position.X);
	Renderer_WriteToPersistentSection(3, L"Pos Y: %f", Char_Position.Y);

	Renderer_WriteToPersistentSection(2, L"RC  X: %u", CharSprite_RenderCoord.X);
	Renderer_WriteToPersistentSection(4, L"RC  Y: %u", CharSprite_RenderCoord.Y);

	Renderer_WriteToBufferCells(getAddress(Char_Sprite), CharSprite_RenderCoord, CharSprite_RenderCoord);
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

