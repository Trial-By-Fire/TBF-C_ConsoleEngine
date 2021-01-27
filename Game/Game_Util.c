// Parent Header
#include "Game_Util.h"



// Functions

// Public

// Level

fn returns(sInt) Level_GetCellAtPosition parameters(Ptr(Level) _level, Vector2D _position)
{
	Stack()
		COORD renderCoord = Convert_Vector2D_ToRenderCoord(_position);

		Ptr(Cell) cellBuffer = (Ptr(Cell))_level;

	return cellBuffer[renderCoord.X * renderCoord.Y].Attributes;
}

fn returns(void) Level_SetCells parameters(Ptr(Level) _level, COORD _firstCell, COORD _lastCell, sInt _cellType) 

SmartScope
{
	Stack()

		DataSize lineOffset = (_firstCell.Y) * ERenderer_Width;
		DataSize colOffset  = _firstCell.X;

		DataSize totalOffset = lineOffset + colOffset;

		Ptr(Cell) levelCellBuffer = (Ptr(Cell))_level;

		Ptr(void) bufferOffset = getAddress(levelCellBuffer[totalOffset]);

		DataSize dataSize = totalOffset;

	lineOffset = (_lastCell.Y) * ERenderer_Width;
	colOffset  =  _lastCell.X;

	totalOffset = lineOffset + colOffset;

	dataSize = totalOffset - dataSize;

	if (dataSize == 0) dataSize = 1;

	Stack()

		Ptr(Cell) setCellBuffer = ScopedAllocate(Cell, dataSize);

	for (DataSize index = 0; index < dataSize; index++)
	{
		setCellBuffer[index].Char.UnicodeChar = 0;
		setCellBuffer[index].Attributes       = _cellType;
	}

	Memory_FormatWithData(bufferOffset, setCellBuffer, dataSize * sizeof(Cell));

	return;
}
SmartScope_End

fn returns(void) Level_Render parameters(Ptr(Level) _level)
{
	Stack()
		COORD 
		screenStart = {               0,                 0 }, 
		screenEnd   = { ERenderer_Width, ERenderer_GameEnd } ;


	Renderer_WriteToBufferCells(_level, screenStart, screenEnd);
}

// Space

fn returns(COORD) Convert_Vector2D_ToRenderCoord parameters(Vector2D _vector)
{
	Stack()
		unbound float32 
			offsetX = (float32)ERenderer_Width   / 2.0f, 
			offsetY = (float32)ERenderer_GameEnd / 2.0f;

	float32 
		convertedX = _vector.X * ((float32)ERenderer_Width   / 2.0f), 
		convertedY = _vector.Y * ((float32)ERenderer_GameEnd / 2.0f);

	Stack()
		COORD renderingCoord;

	renderingCoord.X = (sInt16)(convertedX + offsetX   );	
	renderingCoord.Y = (sInt16)(offsetY    - convertedY);

	if (renderingCoord.X >= ERenderer_Width) renderingCoord.X = ERenderer_Width - 1;

	return renderingCoord;
}


// General Rendering

fn returns(void) ChangeCellsTo_Grey parameters(Ptr(Cell) _renderCells, DataSize _length)
{
	for (DataSize cellIndex = 0; cellIndex < _length; cellIndex++)
	{
		_renderCells[cellIndex].Attributes = FOREGROUND_INTENSITY;
	}
}

fn returns(void) ChangeCellsTo_White parameters(Ptr(Cell) _renderCells, DataSize _length)
{
	for (DataSize cellIndex = 0; cellIndex < _length; cellIndex++)
	{
		_renderCells[cellIndex].Attributes = Console_WhiteCell;
	}
}


// UI

// Text

fn returns(void) UI_Text_Create 

parameters
(
	   Ptr(UI_Text)  _uiText, 
	   Ptr(WideChar) _content, 
	       COORD     _startingCell, 
	       COORD     _endingCell,
		   bool      _shouldCenter
)
{
	// Get length of contents.

	_uiText->Length = wcslen(_content) + 1;

	// Format the contents.

	_uiText->Content = GlobalAllocate(WideChar, _uiText->Length);

	wcscpy_s(_uiText->Content, _uiText->Length, _content);

	_uiText->RenderCells = GlobalAllocate(Cell, _uiText->Length);

	for (DataSize cellIndex = 0; cellIndex < _uiText->Length; cellIndex++)
	{
		_uiText->RenderCells[cellIndex].Char.UnicodeChar = _uiText->Content[cellIndex];
		_uiText->RenderCells[cellIndex].Attributes       = Console_WhiteCell;
	}

	_uiText->StartingCell = _startingCell;
	_uiText->EndingCell   = _endingCell;

	if (_shouldCenter)
	{
		_uiText->StartingCell.X += (ERenderer_Width / 2) - (_uiText->Length / 2);
		_uiText->EndingCell  .X += (ERenderer_Width / 2) + (_uiText->Length / 2);

		_uiText->StartingCell.X--;
		_uiText->EndingCell  .X--;
	}
	else
	{
		_uiText->EndingCell.X += _uiText->Length;
	}
}

fn returns(void) UI_Text_Render parameters(ro Ptr(UI_Text) _uiText)
{
	Renderer_WriteToBufferCells(_uiText->RenderCells, _uiText->StartingCell, _uiText->EndingCell);
}


// Button

fn returns(void) UI_Button_Create 

parameters
(
	   Ptr(UI_Button)     _button, 
	ro Ptr(WideChar)      _text, 
	       COORD          _startingCell, 
	       COORD          _endingCell, 
		   bool           _shouldCenter,
	   Ptr(Void_Function) _callback
)
{
	// Get length of contents.

	_button->Text.Length = wcslen(_text) + 1;

	// Format the contents.

	_button->Text.Content = GlobalAllocate(WideChar, _button->Text.Length);

	wcscpy_s(_button->Text.Content, _button->Text.Length, _text);

	_button->Text.RenderCells = GlobalAllocate(Cell, _button->Text.Length);

	for (DataSize cellIndex = 0; cellIndex < _button->Text.Length; cellIndex++)
	{
		_button->Text.RenderCells[cellIndex].Char.UnicodeChar = _button->Text.Content[cellIndex];
		_button->Text.RenderCells[cellIndex].Attributes       = Console_WhiteCell;
	}

	_button->Text.StartingCell = _startingCell;
	_button->Text.EndingCell   = _endingCell;

	if (_shouldCenter)
	{
		_button->Text.StartingCell.X += (ERenderer_Width / 2) - (_button->Text.Length / 2);
		_button->Text.EndingCell  .X += (ERenderer_Width / 2) + (_button->Text.Length / 2);

		_button->Text.StartingCell.X--;
		_button->Text.EndingCell  .X--;
	}
	else
	{
		_button->Text.EndingCell.X += _button->Text.Length / 2;
	}

	_button->Callback = _callback;
}

fn returns(void) UI_Button_Press parameters(ro Ptr(UI_Button) _uiButton)
{
	_uiButton->Callback();
}

fn returns(void) UI_Button_Render parameters(ro Ptr(UI_Button) _uiButton)
{
	Renderer_WriteToBufferCells(_uiButton->Text.RenderCells, _uiButton->Text.StartingCell, _uiButton->Text.EndingCell);
}


// Grid

fn returns(void) UI_Grid_Add 

parameters
(
	   Ptr(UI_Grid)       _uiGrid, 
	ro Ptr(WideChar)      _text, 
	       COORD          _startingCell, 
	       COORD          _endingCell, 
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
)
{
	if (_uiGrid->Num == 0)
	{
		_uiGrid->Buttons = GlobalAllocate(UI_Button, 1);

		_uiGrid->Num++;
	}
	else
	{
		Stack()
			Address resizeIntermediary = GlobalReallocate(UI_Button, _uiGrid->Buttons, (_uiGrid->Num + 1));

		if (resizeIntermediary != NULL)
		{
			_uiGrid->Buttons = resizeIntermediary;

			_uiGrid->Num++;
		}
		else
		{
			perror("Failed to globally reallocate subscription array.");

			exit(1);
		}
	}

	UI_Button_Create
	(
		getAddress(_uiGrid->Buttons[_uiGrid->Num - 1]), 
		
		_text, 
		_startingCell, 
		_endingCell, 
		_shouldCenter, 
		_callback
	);

	if (_uiGrid->Num != 1)
	{
		ChangeCellsTo_Grey
		(
			_uiGrid->Buttons[_uiGrid->Num -1].Text.RenderCells, 
			_uiGrid->Buttons[_uiGrid->Num -1].Text.Length
		);
	}
}

fn returns(void) UI_Grid_MoveUp parameters(Ptr(UI_Grid) _uiGrid)
{
	Stack()

		Ptr(DataSize) currentIndex = getAddress(_uiGrid->CurrentIndex);

		Ptr(UI_Text) buttonText = getAddress(_uiGrid->Buttons[val(currentIndex)].Text);

	if (val(currentIndex) > 0)
	{
		ChangeCellsTo_Grey(buttonText->RenderCells, buttonText->Length);

		val(currentIndex) =  val(currentIndex) - 1;

		buttonText = getAddress(_uiGrid->Buttons[val(currentIndex)].Text);

		ChangeCellsTo_White(buttonText->RenderCells, buttonText->Length);
	}
}

fn returns(void) UI_Grid_MoveDown parameters(Ptr(UI_Grid) _uiGrid)
{
	Stack()

		Ptr(DataSize) currentIndex = getAddress(_uiGrid->CurrentIndex);

	Ptr(UI_Text) buttonText = getAddress(_uiGrid->Buttons[val(currentIndex)].Text);

	if (val(currentIndex) < _uiGrid->Num)
	{
		ChangeCellsTo_Grey(buttonText->RenderCells, buttonText->Length);

		val(currentIndex) = val(currentIndex) + 1;

		buttonText = getAddress(_uiGrid->Buttons[val(currentIndex)].Text);

		ChangeCellsTo_White(buttonText->RenderCells, buttonText->Length);
	}
}

fn returns(void) UI_Grid_Select parameters(Ptr(UI_Grid) _uiGrid)
{
	UI_Button_Press(getAddress(_uiGrid->Buttons[_uiGrid->CurrentIndex]));
}

fn returns(void) UI_Grid_Render parameters(Ptr(UI_Grid) _uiGrid)
{
	for (DataSize index = 0; index < _uiGrid->Num; index++)
	{
		UI_Button_Render(getAddress(_uiGrid->Buttons[index]));
	}
}


// Grid

fn returns(void) UI_Widget_AddText

parameters
(
	   Ptr(UI_Widget)     _uiWidget,
	ro Ptr(WideChar)      _text,
	       COORD          _startingCell,
	       COORD          _endingCell,
		   bool           _shouldCenter
)
{
	if (_uiWidget->Num_TextUIs == 0)
	{
		_uiWidget->TextUIs = GlobalAllocate(UI_Text, 1);

		_uiWidget->Num_TextUIs++;
	}
	else
	{
		Stack()
			Address resizeIntermediary = GlobalReallocate(UI_Text, _uiWidget->TextUIs, (_uiWidget->Num_TextUIs + 1));

		if (resizeIntermediary != NULL)
		{
			_uiWidget->TextUIs = resizeIntermediary;

			_uiWidget->Num_TextUIs++;
		}
		else
		{
			perror("Failed to globally reallocate subscription array.");

			exit(1);
		}
	}

	UI_Text_Create
	(
		getAddress(_uiWidget->TextUIs[_uiWidget->Num_TextUIs - 1]), 
		
		_text, 
		_startingCell, 
		_endingCell, 
		_shouldCenter
	);
}

fn returns(void) UI_Widget_AddButton 

parameters
(
	   Ptr(UI_Widget)     _uiWidget,
	ro Ptr(WideChar)      _text,
	       COORD          _startingCell,
	       COORD          _endingCell,
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
)
{
	UI_Grid_Add
	(
		getAddress(_uiWidget->Grid), 
		
		_text, 
		_startingCell, 
		_endingCell, 
		_shouldCenter, 
		_callback
	);
}

fn returns(void) UI_Widget_MoveUp parameters(Ptr(UI_Widget) _uiWidget)
{
	UI_Grid_MoveUp(getAddress(_uiWidget->Grid));
}

fn returns(void) UI_Widget_MoveDown parameters(Ptr(UI_Widget) _uiWidget)
{
	UI_Grid_MoveDown(getAddress(_uiWidget->Grid));
}

fn returns(void) UI_Widget_Select parameters(Ptr(UI_Widget) _uiWidget)
{
	UI_Grid_Select(getAddress(_uiWidget->Grid));
}

fn returns(void) UI_Widget_Render parameters(Ptr(UI_Widget) _uiWidget)
{
	for (DataSize index = 0; index < _uiWidget->Num_TextUIs; index++)
	{
		UI_Text_Render(getAddress(_uiWidget->TextUIs[index]));
	}

	UI_Grid_Render(getAddress(_uiWidget->Grid));
}
