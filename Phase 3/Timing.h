#pragma once

// Includes

// C Standard Library

#include <stdbool.h>

// Windows

#include <Windows.h>

// Trial By Fire

#include "C_Assist.h"
#include "FundamentalTypes.h"


// Alias

alias(enum Snapshot_Def) as Snapshot;


// Enums

enum Snapshot_Def
{
	Snapshot_Initial,
	Snapshot_End
};



// Functions

fn returns(floatEP) DeltaTime          parameters(void);

fn returns(uInt64 ) ElapsedTicks       parameters(void);

fn returns(void   ) ProcessCycleTiming parameters(void);

fn returns(floatEP) RefreshTimer       parameters(void);

fn returns(void   ) SetupTiming        parameters(void);

fn returns(bool   ) ShouldRender       parameters(void);

fn returns(void   ) TakeSnapshot       parameters(Snapshot _snapshotFor);
