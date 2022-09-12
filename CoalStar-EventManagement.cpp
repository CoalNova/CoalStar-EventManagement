#include <stdio.h>
#include <SDL.h>
#include "eventmanager.h"

int main(int arcg, char** argv)
{
	int sdlStatus = SDL_Init(SDL_INIT_EVENTS);
	SDL_Window* window = SDL_CreateWindow("CoalWindow", 500, 250, 200, 200, SDL_WINDOW_RESIZABLE);
	Coal::LogReport(Coal::Report{ Coal::ReportLevel::Info , _ReturnAddress(), sdlStatus, 0, "SDL Initialization complete" });
	bool quit = sdlStatus;
	while (!quit)
	{
		quit = Coal::RunInputs();
		quit = Coal::GetInputUp(SDL_SCANCODE_ESCAPE);
	}
	SDL_DestroyWindow(window);
	window = nullptr;
	Coal::SaveReportLog();
	return 0;
}
