#pragma once



// Includes

#include "C_STL.h"
#include "Windows_Includes.h"
#include "LAL.h"



// Aliases (Typedefs)

alias(CONSOLE_SCREEN_BUFFER_INFO) as CSBI;

alias(struct ConsoleData_Def) as ConsoleData;



// Structures

struct ConsoleData_Def
{
	// Procedure Data

	HANDLE ConsoleHandle    ;
	DWORD  CharactersWritten;
	COORD  ScreenPos_00     ;
	CSBI   Csbi_instance    ;
	DWORD  ConsoleSize      ;

	// Render Timing

	float64 ConsoleRefeshTimer   ;
	float64 ConsoleRefeshInterval;
};



// Constants

#define SizeOf_Renderer \
	sizeof(ConsoleData)



// Forward Declarations

fn returns(void) Renderer_LoadModule parameters(void);

fn returns(void) ProcessRenderTiming parameters(float64 _deltaTime);

fn returns(void) ClearRender parameters(void);

fn returns(bool) FillRendererCellsWithWhitespace parameters(void);

fn returns(bool) FormatRendererCells parameters(void);

fn returns(int) print parameters(ro Ptr(char) _message);

fn returns(void) ProcessRender parameters(void);

fn returns(void) RenderFrame parameters(void);

fn returns(void) ResetRendererDrawPosition parameters(void);

fn returns(void) SetupRenderer parameters(void);

fn returns(bool) ShouldRender parameters(void);

fn returns(bool) UpdateRendererInfo parameters(void);



