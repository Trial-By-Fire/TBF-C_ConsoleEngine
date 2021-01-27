#pragma once


#include "Config.h"
#include "LAL.h"
#include "Windows_Platform.h"
#include "State.h"
#include "Renderer.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"



// Functions

// Game must implement this function.
StateObj* LoadGame(void);
