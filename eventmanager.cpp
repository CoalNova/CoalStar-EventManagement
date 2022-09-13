#include "eventmanager.h"
#include <vector>
#include <iostream>
#include <string>
#include <queue>

namespace Coal
{
	std::vector<Input> inputs = std::vector<Input>();
	std::vector<Report> reports = std::vector<Report>();
	std::queue<Event> events = std::queue<Event>();

	bool RunEvents()
	{
		bool quitFlag = false;

		for (int i = 0; i < inputs.size(); i++)
			if (inputs.at(i).state == InputState::Up)
				inputs.erase(inputs.begin() + i--);
			else if (inputs.at(i).state == InputState::Down)
				inputs.at(i).state = InputState::Stay;
		
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{

			auto iter = std::find_if(inputs.begin(), inputs.end(), [e](const Input& evnt) {return (evnt.inputCode & 511) == (unsigned int)e.key.keysym.scancode; });
			if (e.type == SDL_EventType::SDL_KEYDOWN)
			{
				if (iter == inputs.end())
					inputs.push_back(Input{ (unsigned int)e.key.keysym.scancode, InputState::Down });
			}
			if (e.type == SDL_EventType::SDL_KEYUP)
			{
				if (iter != inputs.end())
					iter._Ptr->state = InputState::Up;
			}

			if (e.type == SDL_EventType::SDL_QUIT)
				quitFlag = true;
		}

		while (events.size() > 0)
		{
			Event e = events.front();
			e.function(e.payload);
			events.pop();
		}

		return quitFlag;
	}

	bool GetInputDown(const SDL_Scancode& scancode)
	{
		return GetInputState(scancode) == InputState::Down;
	}

	bool GetInputStay(const SDL_Scancode& scancode)
	{
		return GetInputState(scancode) == InputState::Stay;
	}

	bool GetInputUp(const SDL_Scancode& scancode)
	{
		return GetInputState(scancode) == InputState::Up;
	}

	InputState GetInputState(const SDL_Scancode& scancode)
	{
		auto iter = std::find_if(inputs.begin(), inputs.end(), [scancode](const Input& evnt) {return (evnt.inputCode & 511) == (unsigned int)scancode; });
		if (iter == inputs.end())
			return InputState::None;
		return iter._Ptr->state;
	}


	std::string ReportToString(const Report& report)
	{
		const char* level;
		switch (report.level)
		{
		case ReportLevel::Info:
			level = "Info";
			break;

		case ReportLevel::Warning:
			level = "Warning";
			break;

		case ReportLevel::Error:
			level = "Error";
			break;

		case ReportLevel::Terminal:
			level = "Terminal";
			break;
		default:
			level = "";
		}
		return std::string("[") + level + "](" + std::to_string((unsigned long long)report.caller) + ")(" + std::to_string(report.alpha) + ")(" + std::to_string(report.beta) + ')' + report.description;
	}

	void LogReport(Report report)
	{
		reports.push_back(report);
		if (report.level > ReportLevel::Warning)
		{
			std::cout << ReportToString(report) << '\n';
		}
	}

	void PrintReportLog()
	{
		for (const Report& report : reports)
			std::cout << ReportToString(report) << '\n';

	}

	void SaveReportLog()
	{
		FILE* logfile;
		errno_t err = fopen_s(&logfile, "./logfile.txt", "wb");
		if (err == 0)
			for (const Report& report : reports)
			{
				std::string string = ReportToString(report) + '\n';
				fwrite(string.data(), sizeof(char), string.length(), logfile);
			}
		else
			LogReport(Report{ ReportLevel::Error, _ReturnAddress(), (size_t)err, 0, "log file unopenable" });
	}

	void RegisterEvent(const Event& e)
	{
		//for threadable safety apply conditional predicate ::wait_for 
		events.push(e);
	}


}
