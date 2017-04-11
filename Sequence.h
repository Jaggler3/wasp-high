#pragma once

#include <string>
#include <vector>

#include "Action.h"
#include "Variable.h"
#include "VariableData.h"
#include "Errors.h"
#include "CompilerUtils.h"
#include "Compiler.h"
#include "Script.h"

class Sequence
{
public:
	std::vector<VariableData> &variables = std::vector<VariableData>();
	std::vector<Script> &functions = std::vector<Script>();
	VariableData evaluate(VariableData &res, std::vector<std::string> data, std::vector<Variable> &artifacts, int line = -1);
	int find_by_name(std::string name);
	std::string format(Script script);
	Sequence();
	~Sequence();
	std::vector<Action> &actions = std::vector<Action>();
	Sequence &clear_actions();
};

