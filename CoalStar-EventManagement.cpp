#include <stdio.h>
#include <SDL.h>
#include "eventmanager.h"

int main(int arcg, char** argv)
{
	int sdlStatus = SDL_Init(SDL_INIT_EVENTS);
	Coal::LogReport(Coal::Report{ ((sdlStatus != 0) ? Coal::ReportLevel::Error : Coal::ReportLevel::Info), _ReturnAddress(), sdlStatus, 0, "SDL Initialization complete" });
	SDL_Window* window = SDL_CreateWindow("CoalWindow", 500, 250, 200, 200, SDL_WINDOW_RESIZABLE);
	Coal::LogReport(Coal::Report{ ((window == nullptr) ? Coal::ReportLevel::Error : Coal::ReportLevel::Info), _ReturnAddress(), (int)window, 0, "SDL Window created" });
	bool quit = sdlStatus + (window == nullptr);
	while (!quit)
	{
		quit = Coal::RunInputs();
		quit = Coal::GetInputUp(SDL_SCANCODE_ESCAPE);
	}
	SDL_DestroyWindow(window);
	Coal::LogReport(Coal::Report{ Coal::ReportLevel::Info, _ReturnAddress(), 0,0, "SDL Window closed" });
	window = nullptr;
	SDL_Quit();
	Coal::LogReport(Coal::Report{ Coal::ReportLevel::Info, _ReturnAddress(), 0,0, "SDL Shut down" });
	Coal::SaveReportLog();
	return 0;
}
