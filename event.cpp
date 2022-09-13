#include "event.h"

namespace Coal
{
	Event::Event(const std::function<void(int)>& func, const int& param) : function(func), payload(param)
	{
	}
	void PrintEvent(int i)
	{
		printf("%i\n", i);
	}
	void DoubleEvent(int i)
	{
		printf("Two of %i is %i\n", i, i * 2);
	}
}