// Parent Header
#include "Game_Util.h"



// Functions

// Public

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