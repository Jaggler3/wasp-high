#pragma once

#include "VariableList.h"
#include "Variable.h"
#include "Interpreter.h"
#include <iostream>
#include <vector>

class InterpreterUtils
{
public:
	static void runLoop(VariableList &v, const Variable &condition);
	static void operation(int INDEX, std::vector<Variable> &_vars, Variable &right);
	static void outstr(std::string out);
	static bool ol(int INDEX, std::vector<Variable> &_vars, Variable &right);
};

