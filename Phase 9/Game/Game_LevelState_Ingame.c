// Parent Headers
#include "Game_LevelState_Ingame.h"



// Includes

#include "Game_LevelState_Paused.h"
#include "Game_Util.h"



BSS()

	StateObj Ingame_State;

	UI_Text Ingame_Text;

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

		Ingame_DoneOnce = true;
	}

	Input_SubscribeTo(Key_Enter, getAddress(LevelState_Ingame_OnKeyEnter));
}

fn returns(void) Unload_Ingame parameters(void)
{
	Input_Unsubscribe(Key_Enter, getAddress(LevelState_Ingame_OnKeyEnter));
}

fn returns(void) Update_Ingame parameters(void)
{
}

fn returns(void) Render_Ingame parameters(void)
{
	UI_Text_Render(getAddress(Ingame_Text));
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

