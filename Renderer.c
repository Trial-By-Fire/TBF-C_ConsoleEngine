// Parent Header
#include "Renderer.h"



// Includes

#include "FloatCompare.h"
#include "Input.h"
#include "Memory.h"
#include "Timing.h"



// Static Data

// Private

BSS
(
	Ptr(ConsoleData) Renderer;
)



// Functions

// Public

fn returns(void) Renderer_LoadModule parameters(void)
{
	Renderer = Data_AssignMemory(SizeOf_Renderer);

	SetupRenderer();
}

fn returns(void) ProcessRenderTiming parameters(float64 _deltaTime)
{
	if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
	{
		Renderer->ConsoleRefeshTimer = Renderer->ConsoleRefeshTimer + 0.000001L;

		return;
	}
	else
	{
		Renderer->ConsoleRefeshTimer = Renderer->ConsoleRefeshTimer + _deltaTime;

		return;
	}
}

fn returns(void) ClearRender parameters(void)
{
	if (UpdateRendererInfo())
	{
		Renderer->ConsoleSize = Renderer->Csbi_instance.dwSize.X * Renderer->Csbi_instance.dwSize.Y;

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
		Renderer->ConsoleHandle,
		(TCHAR)' ',
		Renderer->ConsoleSize,
		Renderer->ScreenPos_00,
		getAddress(Renderer->CharactersWritten)
	);
}

fn returns(bool) FormatRendererCells parameters(void)
{
	return FillConsoleOutputAttribute
	(
		Renderer->ConsoleHandle,
		Renderer->Csbi_instance.wAttributes,
		Renderer->ConsoleSize,
		Renderer->ScreenPos_00,
		getAddress(Renderer->CharactersWritten)
	);
}

fn returns(int) print parameters(ro Ptr(char) _message)
{
	return puts(_message);
}

fn returns(void) RenderFrame parameters(void)
{
	Ptr(ro InputData) inputContext = GetInputContext();
	Ptr(ro TimingData) timingContext = GetTimingContext();

	printf("Tick Elapsed        : %llu  \n", timingContext->Cycle_TicksElapsed);
	printf("Timer      (Seconds): %.7Lf \n", Renderer     ->ConsoleRefeshTimer);
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

		Renderer->ConsoleRefeshTimer = 0.0L;
	}
}

fn returns(void) ResetRendererDrawPosition parameters(void)
{
	SetConsoleCursorPosition(Renderer->ConsoleHandle, Renderer->ScreenPos_00);

	return;
}

fn returns(void) SetupRenderer parameters(void)
{
	Renderer->ConsoleRefeshTimer = 0.0L;
	Renderer->ConsoleRefeshInterval = 0.1L;

	Renderer->ScreenPos_00.X = 0;
	Renderer->ScreenPos_00.Y = 0;

	Renderer->ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	return Float64_ApproxGreater(Renderer->ConsoleRefeshTimer, Renderer->ConsoleRefeshInterval) ||
		   Float64_ApproxEqual  (Renderer->ConsoleRefeshTimer, Renderer->ConsoleRefeshInterval)   ;
}

fn returns(bool) UpdateRendererInfo parameters(void)
{
	return GetConsoleScreenBufferInfo(Renderer->ConsoleHandle, getAddress(Renderer->Csbi_instance));
}