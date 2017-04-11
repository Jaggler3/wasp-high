#pragma once

#include <vector>
#include "Variable.h"

class VariableList
{
public:
	int index;
	std::vector<Variable> variables;
	VariableList();
	VariableList(int index, std::vector<Variable> variables);
	~VariableList();
};

