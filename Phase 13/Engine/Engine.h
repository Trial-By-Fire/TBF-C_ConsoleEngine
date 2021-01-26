#pragma once


#include "Config.h"
#include "LAL.h"
#include "State.h"
#include "Renderer.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"



// Functions

// Game must implement this function.
fn returns(Ptr(StateObj)) LoadGame parameters(void);
