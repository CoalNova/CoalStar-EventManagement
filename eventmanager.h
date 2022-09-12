#pragma once
#include "Input.h"
#include "report.h"
#include <SDL.h>


namespace Coal
{
	/// <summary>
	/// Runs through Input queue for SDL
	/// and any other engine systems
	/// </summary>
	/// <returns>Quit Input</returns>
	bool RunInputs();

	bool GetInputDown(const SDL_Scancode& scancode);
	bool GetInputStay(const SDL_Scancode& scancode);
	bool GetInputUp(const SDL_Scancode& scancode);
	InputState GetInputState(const SDL_Scancode& scancode);

	void LogReport(Report report);
	void PrintReportLog();
	void SaveReportLog();
}