#pragma once
#include <algorithm>
#include <string>
class VariableUtils
{
public:
	static bool endsWith(std::string s, std::string suff);
	static std::string valueOf(std::string line);
	static std::string removeDec(std::string val);
};

