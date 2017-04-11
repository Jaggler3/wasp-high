#include "stdafx.h"
#include "VariableUtils.h"

bool VariableUtils::endsWith(std::string s, std::string suffix)
{
	return s.size() >= suffix.size() && s.rfind(suffix) == (s.size() - suffix.size());
}

std::string VariableUtils::valueOf(std::string line)
{
	int i = line.length();
	while (line[i] != ',') { i--; }

	return line.substr(0, i);
}

std::string VariableUtils::removeDec(std::string val)
{
	if (val.find('.') == -1)
	{
		return val;
	}

	int e = val.length();
	while (e > 0)
	{
		e--;

		if (val[e] != '0')
		{
			if (val[e - 1] == '.')
			{
				e--;
			}
			break;
		}
	}

	return val.substr(0, e);
}