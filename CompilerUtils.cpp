#include "stdafx.h"
#include "CompilerUtils.h"

bool CompilerUtils::is_float(std::string in)
{
	std::istringstream iss(in);
	float f;
	iss >> f;
	return iss.eof() && !iss.fail();
}

std::string CompilerUtils::rem_trail(std::string input)
{
	std::string c = "" + input;
	while (c.find(".") != std::string::npos && c.substr(c.length() - 1, 1) == "0" || c.substr(c.length() - 1, 1) == ".")
	{
		c.pop_back();
	}
	if (c != "0") { c.erase(0, c.find_first_not_of('0')); }
	return c;
}