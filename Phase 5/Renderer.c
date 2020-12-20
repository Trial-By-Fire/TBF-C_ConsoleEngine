// Parent Header
#include "Renderer.h"



// Includes

#include "FloatCompare.h"
#include "Input.h"
#include "Memory.h"
#include "Timing.h"



// Static Data

// Private

BSS()

	ConsoleData Renderer;

Data()

	CTS_CWString Renderer_ConsoleTitle = L"TBF C Engine: Phase 5";



// Functions

// Public

fn returns(void) Renderer_LoadModule parameters(void)
{
	SetupRenderer();
}

fn returns(void) ProcessRenderTiming parameters(float64 _deltaTime)
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

fn returns(void) ClearRender parameters(void)
{
	if (UpdateRendererInfo())
	{
		Renderer.Size = Renderer.CSBI_Instance.dwSize.X * Renderer.CSBI_Instance.dwSize.Y;

		if (FillRendererCellsWithWhitespace() && UpdateRendererInfo() && FormatRendererCells())
		{
			ResetRendererDrawPosition();

			return;
		}
		else
		{
			return;   // If any of the conditions fail, return immediately.
		}
	}
}

// Return value tells you if it did the job.
fn returns(bool) FillRendererCellsWithWhitespace parameters(void)
{
	return FillConsoleOutputCharacter
	(
		Renderer.Output_Handle,
		(TCHAR)' ',
		Renderer.Size,
		Renderer.ScreenPos_00,
		getAddress(Renderer.CharactersWritten)
	);
}

fn returns(bool) FormatRendererCells parameters(void)
{
	return FillConsoleOutputAttribute
	(
		Renderer.Output_Handle,
		Renderer.CSBI_Instance.wAttributes,
		Renderer.Size,
		Renderer.ScreenPos_00,
		getAddress(Renderer.CharactersWritten)
	);
}

fn returns(int) print parameters(ro Ptr(char) _message)
{
	return puts(_message);
}

fn returns(void) RenderFrame parameters(void)
{
	Stack()

		Ptr(ro InputData ) inputContext  = GetInputContext ();
		Ptr(ro TimingData) timingContext = GetTimingContext();

	printf("Tick Elapsed        : %llu  \n", timingContext->Cycle_TicksElapsed);
	printf("Timer      (Seconds): %.7Lf \n", Renderer      .RefeshTimer);
	printf("Delta Time (Seconds): %.7Lf \n", timingContext->DeltaTime         );
	printf("Key Pressed         :  %c   \n", inputContext ->LastPressedKey    );

	return;
}

fn returns(void) ProcessRender parameters(void)
{
	if (ShouldRender())
	{
		ClearRender();

		RenderFrame();

		Renderer.RefeshTimer = 0.0L;
	}
}

fn returns(void) ResetRendererDrawPosition parameters(void)
{
	SetConsoleCursorPosition(Renderer.Output_Handle, Renderer.ScreenPos_00);

	return;
}

fn returns(void) SetupRenderer parameters(void)
{
	Stack()
		
		SMALL_RECT consoleWindowCoord;


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

	Renderer.RefeshTimer    = 0.0L;
	Renderer.RefeshInterval = 0.1L;

	Renderer.ScreenPos_00.X = 0;
	Renderer.ScreenPos_00.Y = 0;

	Renderer.CoordSize.X = Renderer_Width ;
	Renderer.CoordSize.Y = Renderer_Height;

	Renderer.Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Renderer.Window_Handle = GetConsoleWindow();

	SetConsoleTitle(Renderer_ConsoleTitle);

	Stack()

		CONSOLE_CURSOR_INFO cursorInfo = { 1, 0 };

	SetConsoleCursorInfo(Renderer.Output_Handle, getAddress(cursorInfo));

	SetConsoleWindowInfo(Renderer.Output_Handle, true, getAddress(consoleWindowCoord));

	SetConsoleScreenBufferSize(Renderer.Output_Handle, Renderer.CoordSize);

	consoleWindowCoord.Left = Renderer.ScreenPos_00.X;
	consoleWindowCoord.Top  = Renderer.ScreenPos_00.Y;

	consoleWindowCoord.Right  = Renderer_Width  - 1;
	consoleWindowCoord.Bottom = Renderer_Height - 1;

	SetConsoleWindowInfo(Renderer.Output_Handle, true, getAddress(consoleWindowCoord));

	Stack()

		sInt x = GetSystemMetrics(SM_CXSCREEN) / 2;
		sInt y = GetSystemMetrics(SM_CXSCREEN) / 2;

		sInt Window_Width  = (x - ((Renderer_Width  / 2) * 8)) - 5;
		sInt Window_Height = (y - ((Renderer_Height / 2) * 8)) - 5;

	SetWindowPos(Renderer.Window_Handle, 
				 HWND_TOP,
				 Window_Width,
				 Window_Height,
				 0,
				 0,
				 SWP_NOSIZE
	);

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	return Float64_ApproxGreater(Renderer.RefeshTimer, Renderer.RefeshInterval) ||
		   Float64_ApproxEqual  (Renderer.RefeshTimer, Renderer.RefeshInterval)   ;
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

fn returns(bool) UpdateRendererInfo parameters(void)
{
	return GetConsoleScreenBufferInfo(Renderer.Output_Handle, getAddress(Renderer.CSBI_Instance));
}