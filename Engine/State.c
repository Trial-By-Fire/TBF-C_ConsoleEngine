// Parent Header
#include "State.h"



// Includes

#include "State_Intro.h"
#include "Engine.h"


enum 
{
	 EFocusState_Game,
	 EFocusState_Logs
};




// State

Data()

	Ptr(StateObj) CurrentState = NULL;

	uInt FocusState = EFocusState_Game;



// Functions

// Public

fn returns(void) State_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			switch (FocusState)
			{
				case EFocusState_Logs:
				{
					Renderer_Logs_ScrollUp();

					break;
				}
			}

			break;
		}
	}
}

fn returns(void) State_OnKeyArrowDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			switch (FocusState)
			{
				case EFocusState_Logs:
				{
					Renderer_Logs_ScrollDown();

					break;
				}
			}

			break;
		}
	}
}

fn returns(void) State_OnKeyTab parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			switch (FocusState)
			{
				case EFocusState_Game:
				{
					FocusState = EFocusState_Logs;

					break;
				}
				case EFocusState_Logs:
				{
					FocusState = EFocusState_Game;

					break;
				}
			}

			break;
		}
	}
}


fn returns(void) State_LoadModule parameters(void)
{
	CurrentState = GetIntroState();

	CurrentState->Load();

	Input_SubscribeTo(Key_Arrow_Up  , getAddress(State_OnKeyArrowUp  ));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(State_OnKeyArrowDown));
	Input_SubscribeTo(Key_Tab       , getAddress(State_OnKeyTab      ));
}

fn returns(void) State_SetState parameters(Ptr(StateObj) _state)
{
	if (CurrentState != NULL)
	{
		CurrentState->Unload();
	}

	CurrentState = _state;

	CurrentState->Load();
}

fn returns(void) State_Update parameters(void)
{
	if (CurrentState != NULL)
	{
		CurrentState->Update();
	}
}

fn returns(void) State_Render parameters(void)
{
	if (CurrentState != NULL)
	{
		CurrentState->Render();
	}
}

fn returns(void) State_LoadGame parameters(void)
{
	State_SetState(LoadGame());
}
