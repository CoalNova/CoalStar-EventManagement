#include "eventmanager.h"
#include <vector>
#include <iostream>
#include <string>

namespace Coal
{
	std::vector<Input> Inputs = std::vector<Input>();
	std::vector<Report> reports = std::vector<Report>();

	bool RunInputs()
	{
		bool quitFlag = false;
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			for (int i = 0; i < Inputs.size(); i++)
				if (Inputs.at(i).state == InputState::Up)
					Inputs.at(i).state = InputState::None;
				else if (Inputs.at(i).state == InputState::None)
					Inputs.erase(Inputs.begin() + i--);

			auto iter = std::find_if(Inputs.begin(), Inputs.end(), [e](const Input& evnt) {return (evnt.inputCode & 511) == (unsigned int)e.key.keysym.scancode; });
			if (e.type == SDL_EventType::SDL_KEYDOWN)
			{
				if (iter == Inputs.end())
					Inputs.push_back(Input{ (unsigned int)e.key.keysym.scancode, InputState::Down });
				else
					iter._Ptr->state = InputState::Stay;
			}
			if (e.type == SDL_EventType::SDL_KEYUP)
			{
				if (iter != Inputs.end())
					iter._Ptr->state = InputState::Up;
			}

			if (e.type == SDL_EventType::SDL_QUIT)
				quitFlag = true;
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
		auto iter = std::find_if(Inputs.begin(), Inputs.end(), [scancode](const Input& evnt) {return (evnt.inputCode & 511) == (unsigned int)scancode; });
		if (iter == Inputs.end())
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
			LogReport(Report{ ReportLevel::Error, _ReturnAddress(), err, 0, "log file unopenable" });
	}


}
