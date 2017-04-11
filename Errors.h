#pragma once

#include <iostream>
#include <string>

class Errors
{
public:
	enum ErrorType
	{
		SET_TO_FUNC,
		UNKNOWN,
		VAR_UNDEF,
	};
	static void exit(ErrorType type, std::string data = "", int line = -1);
};

