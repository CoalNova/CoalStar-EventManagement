#pragma once
#include <functional>

namespace Coal
{
	void PrintEvent(int i);
	void DoubleEvent(int i);

	struct Event
	{
		Event(const std::function<void(int)>& func, const int& param);
		std::function<void(int)> function;
		int payload;
	};
}