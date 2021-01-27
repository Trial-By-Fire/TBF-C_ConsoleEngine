// Parent Header
#include "Game_EntryState.h"



BSS()

	StateObj MainMenu;

Data()
	bool 
	Log_Load   = true;
	Log_Unload = true;



// Functions

fn returns(void) MainMenu_Load parameters(void)
{
	if (Log_Load)
	{
		Renderer_WriteToLog(L"Loaded: Main Menu");

		Log_Load = false;
	}
}

fn returns(void) MainMenu_Unload parameters(void)
{
	if (Log_Unload)
	{
		Renderer_WriteToLog(L"Unload: Main Menu");

		Log_Unload = false;
	}
}

fn returns(void) MainMenu_Update parameters(void)
{
	if (Input_GetKeyTap(Key_Arrow_Down, 3))
	{
		Cycler_Quit();
	}
}

fn returns(void) MainMenu_Render parameters(void)
{
}



// Engine Entrypoint

fn returns(Ptr(StateObj)) LoadGame parameters(void)
{
	MainMenu.Load   = getAddress(MainMenu_Load  );
	MainMenu.Unload = getAddress(MainMenu_Unload);
	MainMenu.Update = getAddress(MainMenu_Update);
	MainMenu.Render = getAddress(MainMenu_Render);

	return getAddress(MainMenu);
}



