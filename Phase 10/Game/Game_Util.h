#pragma once



// Includes

#include "Engine/Engine.h"



// Aliases

// Space

alias(struct Vector2D_Def) as Vector2D;


// UI

alias(struct UI_Text_Def  ) as UI_Text;
alias(struct UI_Button_Def) as UI_Button;
alias(struct UI_Grid_Def  ) as UI_Grid;
alias(struct UI_Widget_Def) as UI_Widget;



// Structs

// Space

struct Vector2D_Def
{
	float32 X;
	float32 Y;
};

// UI

struct UI_Text_Def
{
	Ptr(WideChar) Content;

	DataSize Length;

	Ptr(Cell) RenderCells;

	COORD StartingCell, EndingCell;
};

struct UI_Button_Def
{
	UI_Text Text;

	Ptr(Void_Function) Callback;
};

struct UI_Grid_Def
{
	Ptr(UI_Button) Buttons;

	DataSize Num;

	DataSize CurrentIndex;
};

struct UI_Widget_Def
{
	Ptr(UI_Text) TextUIs;

	DataSize Num_TextUIs;

	//Ptr(UI_Grid) Grids;

	UI_Grid Grid;
};



// Functions

// Space

fn returns(COORD) Convert_Vector2D_ToRenderCoord parameters(Vector2D _vector);

// General Rendering

fn returns(void) ChangeCellsTo_Grey parameters(Ptr(Cell) _renderCells, DataSize _length);

fn returns(void) ChangeCellsTo_White parameters(Ptr(Cell) _renderCells, DataSize _length);

// UI

fn returns(void) UI_Text_Create 

parameters
(
	   Ptr(UI_Text)  _uiText, 
	   Ptr(WideChar) _content, 
	       COORD     _startingCell, 
	       COORD     _endingCell,
	       bool      _shouldCenter
);

fn returns(void) UI_Text_Render parameters(ro Ptr(UI_Text) _uiText);

fn returns(void) UI_Button_Create 

parameters
(
	   Ptr(UI_Button)     _button, 
	ro Ptr(WideChar)      _text, 
	       COORD          _startingCell, 
	       COORD          _endingCell, 
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
);

fn returns(void) UI_Button_Press  parameters(ro Ptr(UI_Button) _uiButton);
fn returns(void) UI_Button_Render parameters(ro Ptr(UI_Button) _uiButton);

fn returns(void) UI_Grid_Add 

parameters
(
	   Ptr(UI_Grid)       _uiGrid, 
	ro Ptr(WideChar)      _text, 
	       COORD          _startingCell, 
	       COORD          _endingCell, 
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
);

fn returns(void) UI_Grid_MoveUp   parameters(Ptr(UI_Grid) _uiGrid);
fn returns(void) UI_Grid_MoveDown parameters(Ptr(UI_Grid) _uiGrid);
fn returns(void) UI_Grid_Select   parameters(Ptr(UI_Grid) _uiGrid);
fn returns(void) UI_Grid_Render   parameters(Ptr(UI_Grid) _uiGrid);

fn returns(void) UI_Widget_AddText

parameters
(
	   Ptr(UI_Widget)     _uiWidget,
	ro Ptr(WideChar)      _text,
	       COORD          _startingCell,
	       COORD          _endingCell
);

fn returns(void) UI_Widget_AddButton 

parameters
(
	   Ptr(UI_Widget)     _uiWidget,
	ro Ptr(WideChar)      _text,
	       COORD          _startingCell,
	       COORD          _endingCell,
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
);

fn returns(void) UI_Widget_MoveUp   parameters(Ptr(UI_Widget) _uiWidget);
fn returns(void) UI_Widget_MoveDown parameters(Ptr(UI_Widget) _uiWidget);
fn returns(void) UI_Widget_Select   parameters(Ptr(UI_Widget) _uiWidget);
fn returns(void) UI_Widget_Render   parameters(Ptr(UI_Widget) _uiWidget);


