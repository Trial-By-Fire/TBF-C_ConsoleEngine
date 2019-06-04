#pragma once

// Includes

#include <stdbool.h>

// Trial By Fire

#include "C_Assist.h"



// Functions

fn returns(void) ClearRender     parameters(void);

fn returns(int ) print           parameters(readonly Ptr(char) _stringToPrint);

fn returns(void) ProcessRenderer parameters(void);

fn returns(void) SetupRenderer   parameters(void);

fn returns(bool) ShouldRender    parameters(void);
