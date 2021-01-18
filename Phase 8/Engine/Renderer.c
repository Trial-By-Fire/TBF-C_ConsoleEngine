// Parent Header
#include "Renderer.h"



// Includes

#include "FloatCompare.h"
#include "Input.h"
#include "Memory.h"
#include "Timing.h"
#include "State.h"



// Static Data

// Private

BSS()

	Ptr(CHAR_INFO) Buffer;

	RendererData Renderer;
	ScreenInfo   Screen;

	Line Border_GameDebug    ;
	Line Border_LogPersistent;

	// Eliminate these?

	Line DebugLogSection  [ERenderer_DebugLogSize         ];
	Line PersistentSection[ERenderer_PersistentSectionSize];

Data()

	ro CTS_CWString Renderer_ConsoleTitle = L"TBF C Engine: Phase 8";

	ro COORD Console_ScreenPos_00 = 
	{
		0,  // X
		0   // Y
	};



// Forward Declarations

fn returns(void) DrawGameScanlines     parameters(void);
fn returns(void) InitalizeData         parameters(void);
fn returns(void) SetupConsole          parameters(void);
fn returns(bool) ShouldRender          parameters(void);
fn returns(bool) UpdateConsoleInfo     parameters(void);
fn returns(void) UpdateSizeAndPosition parameters(void);



// Functions

// Public

fn returns(void) Renderer_Clear parameters(void)
{
	if (UpdateConsoleInfo())
	{
		Memory_FormatByFill(CHAR_INFO, Buffer, 0, ERenderer_Width * ERenderer_Height);
	}
}

// Return value tells you if it did the job.
fn returns(bool) Renderer_FillCellsWithWhitespace parameters(void)
{
	return FillConsoleOutputCharacter
	(
		Renderer.Output_Handle,
		(TCHAR)' ',
		Renderer.BufferSize,
		Console_ScreenPos_00,
		getAddress(Renderer.CharactersWritten)
	);
}

fn returns(bool) Renderer_FormatCells parameters(void)
{
	return FillConsoleOutputAttribute
	(
		Renderer.Output_Handle,
		Renderer.CSBI_Instance.wAttributes,
		Renderer.BufferSize,
		Console_ScreenPos_00,
		getAddress(Renderer.CharactersWritten)
	);
}

fn returns(ro Ptr(RendererData)) Renderer_GetContext(void)
{
	return getAddress(Renderer);
}

fn returns(void) Renderer_LoadModule parameters(void)
{
	SetupConsole();

	InitalizeData();

	// Setup Console to ideal configuration.

	SetConsoleTitle(Renderer_ConsoleTitle);

	UpdateSizeAndPosition();

	return;
}

fn returns(void) Renderer_ProcessTiming parameters(float64 _deltaTime)
{
	if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
	{
		Renderer.RefeshTimer = Renderer.RefeshTimer + 0.000001L;

		return;
	}
	else
	{
		Renderer.RefeshTimer = Renderer.RefeshTimer + _deltaTime;

		return;
	}
}

fn returns(void) Renderer_RenderFrame parameters(void)
{
	// Renders buffer to console.
	WriteConsoleOutput(Renderer.Output_Handle, Buffer, Renderer.CoordSize, Console_ScreenPos_00, getAddress(Renderer.Size));

	return;
}

fn returns(void) Renderer_ResetDrawPosition parameters(void)
{
	SetConsoleCursorPosition(Renderer.Output_Handle, Console_ScreenPos_00);

	return;
}

fn returns(void) Renderer_UnloadModule parameters(void)
{
	if (Unbind_IOBufferTo_Console() != true)
	{
		perror("Failed to unbind standard IO from renderer console");

		exit(1);
	}

	if (FreeConsole() != true)
	{
		perror("Failed to free renderer console properly.");

		exit(1);
	}
}

fn returns(void) Renderer_Update parameters(void)
{
	if (ShouldRender())
	{
		Renderer_Clear();

		DrawGameScanlines();

		State_Render();

		Stack()

		COORD 
			startingCell = { 0              , ERenderer_BorderLine}, 
			finalCell    = { ERenderer_Width, ERenderer_BorderLine};

		Renderer_WriteToBufferCells(getAddress(Border_GameDebug), startingCell, finalCell);

		startingCell.Y = ERenderer_DebugPersistentStart - 1;
		finalCell   .Y = ERenderer_DebugPersistentStart - 1;

		Renderer_WriteToBufferCells(getAddress(Border_LogPersistent), startingCell, finalCell);

		for (DataSize index = 0; index < ERenderer_DebugLogSize; index++)
		{
			startingCell.Y = ERenderer_DebugStart + index;
			finalCell   .Y = ERenderer_DebugStart + index;

			Renderer_WriteToBufferCells(getAddress(DebugLogSection[index]), startingCell, finalCell);
		}

		for (DataSize index = 0; index < ERenderer_PersistentSectionSize; index++)
		{
			startingCell.Y = ERenderer_DebugPersistentStart + index;
			finalCell   .Y = ERenderer_DebugPersistentStart + index;

			Renderer_WriteToBufferCells(getAddress(PersistentSection[index]), startingCell, finalCell);
		}

		Renderer_RenderFrame();

		Renderer.RefeshTimer = 0.0L;
	}
}

fn returns(void) Renderer_WriteToBufferCells parameters(Ptr(Cell) _cell, COORD _initalCell, COORD _finalCell)
{
	Stack()

		DataSize lineOffset = (_initalCell.Y) * ERenderer_Width;
		DataSize colOffset  = _initalCell.X;

		DataSize totalOffset = lineOffset + colOffset;

		Ptr(void) bufferOffset = getAddress(Buffer[totalOffset]);

		DataSize dataSize = totalOffset;

	lineOffset = (_finalCell.Y) * ERenderer_Width;
	colOffset  =  _finalCell.X;

	totalOffset = lineOffset + colOffset;

	dataSize = totalOffset - dataSize;

	if (dataSize == 0) dataSize = 1;

	Memory_FormatWithData(bufferOffset, _cell, dataSize * sizeof(Cell));

	return;
}

fn returns(void) Renderer_WriteToLog parameters(Ptr(WideChar) _logString)
{
	Stack()

		unbound uInt nextLine = 0;

		DataSize logLength = wcslen(_logString);
		DataSize linePos   = 0;

	for (DataSize index = 0; index < logLength; index++)
	{
		if (linePos > ERenderer_Width - 1)
		{
			nextLine++;

			linePos = 0;
		}

		if (nextLine == 18)
		{
			nextLine = 0;
		}

		DebugLogSection[nextLine][linePos].Char.UnicodeChar = _logString[index];
		DebugLogSection[nextLine][linePos].Attributes       = Console_WhiteCell;

		linePos++;
	}

	for (DataSize index = linePos; index < ERenderer_Width; index++)
	{
		DebugLogSection[nextLine][index].Char.UnicodeChar = 0;
		DebugLogSection[nextLine][index].Attributes       = 0;
	}

	nextLine++;

	if (nextLine == 18)
	{
		nextLine = 0;
	}

	Stack()

		Cell fillInfo;

	fillInfo.Char.UnicodeChar = L'-';
	fillInfo.Attributes       = Console_WhiteCell;

	for (DataSize index = 0; index < ERenderer_Width; index++)
	{
		DebugLogSection[nextLine][index] = fillInfo;
	}
}

// Note: Row starts at 1.
fn returns(void) Renderer_WriteToPersistentSection parameters(sInt _row, Ptr(WideChar) _lineformat, ...)
{
	Stack()

		WideChar TranslationBuffer[ERenderer_Width];

		Ptr(Cell) PersistentSubSection = PersistentSection[_row - 1];

		sInt CellsFormatted;

		va_list argList;


	va_start(argList, _lineformat);

	CellsFormatted = 
		
		// Windows hard coding.
		_vswprintf_s_l
		(
			TranslationBuffer, 
			ERenderer_Width, 
			_lineformat, 
			NULL,
			argList
		);

	va_end(argList);

	for (DataSize index = 0; index < CellsFormatted; index++)
	{
		PersistentSubSection[index].Char.UnicodeChar = TranslationBuffer[index];
		PersistentSubSection[index].Attributes       = Console_WhiteCell;
	}

	for (DataSize index = CellsFormatted + 1; index < ERenderer_Width; index++)
	{
		PersistentSubSection[index].Char.UnicodeChar = NULL;
		PersistentSubSection[index].Attributes       = NULL;
	}
}



// Private

fn returns(void) DrawGameScanlines parameters(void)
{
	Stack()

		unbound COORD cellIndex = { 0, 0 };

		ro WideChar blockChar = '-';

		Cell cellUnit;

	cellUnit.Char.UnicodeChar = blockChar;
	cellUnit.Attributes       = FOREGROUND_INTENSITY;

	Stack()

		Cell cellLine[ERenderer_Width];

	for (DataSize index = 0; index < ERenderer_Width; index++)
	{
		cellLine[index] = cellUnit;
	}

	Stack()

		COORD cellIndex_End = { ERenderer_Width, cellIndex.Y };

	Renderer_WriteToBufferCells(getAddress(cellLine), cellIndex, cellIndex_End);

	cellIndex.Y++;

	if (cellIndex.X >= ERenderer_Width)
	{
		cellIndex.X = 0;

		cellIndex.Y++;
	}

	if (cellIndex.Y > ERenderer_GameEnd)
	{
		cellIndex.X = 0;

		cellIndex.Y = 0;
	}
}

fn returns(void) InitalizeData parameters(void)
{
	// Setup Necessary Data

	Screen.Center.X = GetSystemMetrics(SM_CXSCREEN) / 2;
	Screen.Center.Y = GetSystemMetrics(SM_CYSCREEN) / 2;

	Renderer.ScreenPosition.X = (Screen.Center.X - ((ERenderer_Width  / 2) * 8)) - 20;
	Renderer.ScreenPosition.Y = (Screen.Center.Y - ((ERenderer_Height / 2) * 8)) - 200;

	Renderer.RefeshTimer    = 0.0L;
	Renderer.RefeshInterval = 0.1L;

	Renderer.CoordSize.X = ERenderer_Width ;
	Renderer.CoordSize.Y = ERenderer_Height;

	Renderer.Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Renderer.Window_Handle = GetConsoleWindow();

	Renderer.Size.Left   = Console_ScreenPos_00.X;
	Renderer.Size.Top    = Console_ScreenPos_00.Y;
	Renderer.Size.Right  = ERenderer_Width  - 1;
	Renderer.Size.Bottom = ERenderer_Height - 1;

	Renderer.CursorSettings.dwSize   = Console_Cursor_MinSize;
	Renderer.CursorSettings.bVisible = Console_Cursor_NotVisible;

	Buffer = GlobalAllocate(CHAR_INFO, ERenderer_Width * ERenderer_Height);

	Memory_FormatByFill(CHAR_INFO, Buffer, 0, ERenderer_Width * ERenderer_Height);

	Stack()

		Cell borderCell; 
	
	borderCell.Char.UnicodeChar = '='; 
	borderCell.Attributes       = Console_WhiteCell;

	for (DataSize index = 0; index < ERenderer_Width; index++)
	{
		Border_GameDebug    [index] = borderCell;
		Border_LogPersistent[index] = borderCell;
	}

	return;
}

// Do initial request and IO binding for console interface.
fn returns(void) SetupConsole parameters(void)
{
	if (RequestConsole() != true)
	{
		perror("Failed to get console for rendering from operating system.");

		exit(1);
	}

	if (Bind_IOBufferTo_Console() != true)
	{
		perror("Failed to bind standard IO to renderer console.");

		exit(1);
	}

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	return Float64_ApproxGreater(Renderer.RefeshTimer, Renderer.RefeshInterval) ||
		   Float64_ApproxEqual  (Renderer.RefeshTimer, Renderer.RefeshInterval)   ;
}

fn returns(bool) UpdateConsoleInfo parameters(void)
{
	return GetConsoleScreenBufferInfo(Renderer.Output_Handle, getAddress(Renderer.CSBI_Instance));
}

fn returns(void) UpdateSizeAndPosition parameters(void)
{
	// Set desired cursor preferences.
	SetConsoleCursorInfo(Renderer.Output_Handle, getAddress(Renderer.CursorSettings));

	// Change the window size.
	SetConsoleWindowInfo(Renderer.Output_Handle, true, getAddress(Renderer.Size));

	// Update the buffer size.
	SetConsoleScreenBufferSize(Renderer.Output_Handle, Renderer.CoordSize);

	// Update the window size.
	SetConsoleWindowInfo(Renderer.Output_Handle, true, getAddress(Renderer.Size));

	SetWindowPos
	(
		Renderer.Window_Handle,
		HWND_TOP,
		Renderer.ScreenPosition.X,
		Renderer.ScreenPosition.Y,
		0,
		0,
		SWP_NOSIZE
	);

	return;
}