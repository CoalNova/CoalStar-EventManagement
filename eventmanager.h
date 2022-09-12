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

	/// <summary>
	/// Checks SDL events to check if the provided scancode's associated input is depressed
	/// </summary>
	/// <param name="scancode">SDL scancode for desired input</param>
	/// <returns>If input depressed</returns>
	bool GetInputDown(const SDL_Scancode& scancode);
	/// <summary>
	/// Checks SDL events to check if the provided scancode's associated input is held
	/// </summary>
	/// <param name="scancode">SDL scancode for desired input</param>
	/// <returns>If input held</returns>
	bool GetInputStay(const SDL_Scancode& scancode);
	/// <summary>
	/// Checks SDL events to check if the provided scancode's associated input is released
	/// </summary>
	/// <param name="scancode">SDL scancode for desired input</param>
	/// <returns>If input released</returns>
	bool GetInputUp(const SDL_Scancode& scancode);
	/// <summary>
	/// Returns the 'state' of the associated SDL scancode
	/// </summary>
	/// <param name="scancode">SDL scancode for desired input</param>
	/// <returns>The state of the input, either InputState::Down, ::Stay, ::Up, all else ::None</returns>
	InputState GetInputState(const SDL_Scancode& scancode);

	/// <summary>
	/// Logs a report
	/// </summary>
	/// <param name="report">the report to be logged</param>
	void LogReport(Report report);
	/// <summary>
	/// Prints the Report Log to the console
	/// </summary>
	void PrintReportLog();
	/// <summary>
	/// Saves the Report Log to the disk, in the current directory
	/// </summary>
	void SaveReportLog();
}