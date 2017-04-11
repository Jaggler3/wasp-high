#pragma once

#include <vector>
#include <string>
#include "VariableData.h"
#include "Tokenizer.h"

class Script
{
public:
	std::vector<std::string> &symbols = std::vector<std::string>();
	std::vector<int> &lines = std::vector<int>();
	Script();
	Script(std::string script);
	~Script();
};

