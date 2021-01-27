#pragma once



#include "LAL.h"



// Aliases (Typedefs)

typedef enum ExecFlags_Def ExecFlags;



// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Sucess = 0,
};



// Functions

ExecFlags EntryPoint(void);

