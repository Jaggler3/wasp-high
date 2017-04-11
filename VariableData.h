#pragma once

#include <vector>

#include "Variable.h"

class VariableData
{
public:
	std::string name;
	enum Reference
	{
		NONE,
		ARTIFACT,
		//GLOBAL, /* globals are now in a script file that is loaded */
		CELL,
		FUNC_EVAL,
	};
	Reference ref;
	int ref_index = -1;
	VariableData();
	~VariableData();
};

