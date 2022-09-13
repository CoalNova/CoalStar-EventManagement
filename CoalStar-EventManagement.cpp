#include <stdio.h>
#include <SDL.h>
#include "eventmanager.h"

int main(int arcg, char** argv)
{
	int sdlStatus = SDL_Init(SDL_INIT_EVENTS);
	Coal::LogReport(Coal::Report{ ((sdlStatus != 0) ? Coal::ReportLevel::Error : Coal::ReportLevel::Info), _ReturnAddress(), (size_t)sdlStatus, 0, "SDL Initialization complete" });
	SDL_Window* window = SDL_CreateWindow("CoalWindow", 500, 250, 200, 200, SDL_WINDOW_RESIZABLE);
	Coal::LogReport(Coal::Report{ ((window == nullptr) ? Coal::ReportLevel::Error : Coal::ReportLevel::Info), _ReturnAddress(), (size_t)window, 0, "SDL Window created" });
	bool quit = sdlStatus + (window == nullptr);

	while (!quit)
	{
		quit = Coal::RunEvents();
		quit = Coal::GetInputUp(SDL_SCANCODE_ESCAPE);
		if (Coal::GetInputDown(SDL_SCANCODE_A))
			Coal::RegisterEvent(Coal::Event{ Coal::PrintEvent,  7 });
		if (Coal::GetInputDown(SDL_SCANCODE_S))
			Coal::RegisterEvent(Coal::Event{ Coal::PrintEvent,  8 });
		if (Coal::GetInputDown(SDL_SCANCODE_D))
			Coal::RegisterEvent(Coal::Event{ Coal::DoubleEvent,  9 });
		if (Coal::GetInputDown(SDL_SCANCODE_W))
			Coal::RegisterEvent(Coal::Event{ Coal::DoubleEvent,  7 });

	}
	SDL_DestroyWindow(window);
	Coal::LogReport(Coal::Report{ Coal::ReportLevel::Info, _ReturnAddress(), 0,0, "SDL Window closed" });
	window = nullptr;
	SDL_Quit();
	Coal::LogReport(Coal::Report{ Coal::ReportLevel::Info, _ReturnAddress(), 0,0, "SDL Shut down" });
	Coal::SaveReportLog();
	return 0;
}
