#pragma once

#include "Variable.h"
#include "VariableData.h"

class Action
{
public:
	enum ActionType
	{
		NONE,
		VAR_DEC,
		VAR_DEL,
		INT_INCR,
		INT_DECR,
		IF_BEGIN,
		IF_END,
		MULT_EQ,
		PRINT,
		S_PRINT,
		RESTART,
		FUNC_DEC
	};
	ActionType type = ActionType::NONE;
	VariableData at; //actor
	Variable ad; //acted
	Action();
	Action(ActionType type, VariableData at, Variable ad);
	Action clone();
	~Action();
};