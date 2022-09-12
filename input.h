#pragma once
#include <SDL.h>

namespace Coal
{
	enum class InputState {Down, Stay, Up, None, UNUSED_LAST};
	struct Input
	{
		//SDL ScanCodes are 0x000 - 0x11a
		//Prioritizing bits 0-9 for scancodes, subsequent blocks can be used for seperate data
		unsigned int inputCode; 
		InputState state;
	};
}