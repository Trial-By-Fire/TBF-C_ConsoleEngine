// Parent Header
#include "Game_LevelState.h"



// Includes

#include "Game_EntryState.h"
#include "Game_LevelState_Ingame.h"
#include "Game_Util.h"



BSS()

	StateObj LevelState;

Data()

	Ptr(StateObj) LevelState_CurrentSubstate = NULL;



// Functions

// Class Public

fn returns(void) Load_Level parameters(void)
{
	LevelState_SetSubstate(GetIngameState());
}

fn returns(void) Unload_Level parameters(void)
{
	LevelState_CurrentSubstate->Unload();

	LevelState_CurrentSubstate = NULL;
}

fn returns(void) Update_Level parameters(void)
{
	LevelState_CurrentSubstate->Update();
}

fn returns(void) Render_Level parameters(void)
{
	LevelState_CurrentSubstate->Render();
}



// Public

fn returns( Ptr(StateObj)) GetLevelState parameters(void)
{
	unbound bool stateConstructed = false;

	if (!stateConstructed)
	{
		LevelState.Load   = getAddress(Load_Level  );
		LevelState.Unload = getAddress(Unload_Level);
		LevelState.Update = getAddress(Update_Level);
		LevelState.Render = getAddress(Render_Level);

		stateConstructed = true;
	}

	return getAddress(LevelState);
}

fn returns(void) LevelState_SetSubstate parameters( Ptr(StateObj) _state)
{
	if (LevelState_CurrentSubstate != NULL)
	{
		LevelState_CurrentSubstate->Unload();
	}

	LevelState_CurrentSubstate = _state;

	LevelState_CurrentSubstate->Load();
}
