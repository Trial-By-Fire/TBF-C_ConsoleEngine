#pragma once



// Includes

#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"



// Aliases (Typedefs)

alias(CONSOLE_SCREEN_BUFFER_INFO) as CSBI;

alias(struct ConsoleData_Def) as ConsoleData;



// Structures

struct ConsoleData_Def
{
	// Procedure Data

	HWND   Window_Handle;
	HANDLE Output_Handle;
	DWORD  CharactersWritten  ;
	COORD  ScreenPos_00     ;
	COORD  CoordSize;
	CSBI   CSBI_Instance    ;
	DWORD  Size      ;

	// Render Timing

	float64 RefeshTimer   ;
	float64 RefeshInterval;
};



// Constants

#define SizeOf_Renderer \
	sizeof(ConsoleData)

#define Renderer_Width \
	80

#define Renderer_Height \
	48



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

fn returns(void) Renderer_UnloadModule parameters(void);

fn returns(bool) UpdateRendererInfo parameters(void);



