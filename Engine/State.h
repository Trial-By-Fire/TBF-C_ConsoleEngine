#pragma once



// Includes

#include "LAL.h"



// Aliases (Typedefs)

alias(struct StateObj_Def) as StateObj;



// Structs

struct StateObj_Def
{
	Ptr(Void_Function) Load  ;
	Ptr(Void_Function) Unload; 
	Ptr(Void_Function) Update;
	Ptr(Void_Function) Render;
};



// Functions

fn returns(void) State_LoadModule parameters(void);

fn returns(void) State_SetState(Ptr(StateObj) _state);

fn returns(void) State_Update parameters(void);

fn returns(void) State_Render parameters(void);

fn returns(void) State_LoadGame parameters(void);

