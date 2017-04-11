#include "stdafx.h"
#include "InterpreterUtils.h"

void InterpreterUtils::runLoop(VariableList &v, const Variable &condition)
{
	//similar to do-while
	Interpreter::iOL::LC = false;
	VariableList led = Interpreter::e(Interpreter::iOL::LD, v);
	v = led;
	while (led.variables[led.index].value != condition.value)
	{
		v = led = Interpreter::e(Interpreter::iOL::LD, v);
	}
}

void InterpreterUtils::operation(int INDEX, std::vector<Variable> &_vars, Variable &right)
{
	if (Interpreter::iOL::PRNT)
	{
		outstr(right.value);
		Interpreter::iOL::PRNT = false;
	}
	else if (InterpreterUtils::ol(INDEX, _vars, right)) { }
	else if (Interpreter::iOL::SI)
	{
		Interpreter::iOL::SI = false;
		if (Interpreter::iOL::OP_D)
		{
			Interpreter::iOL::OP_D = false;
			Interpreter::iOL::COI = (std::stoi(_vars[INDEX].value) - std::stoi(right.value)) <= 0;
		}
		else
		{
			Interpreter::iOL::COI = _vars[INDEX].value != right.value;
		}

		Interpreter::iOL::COI = Interpreter::iOL::FI ? !Interpreter::iOL::COI : Interpreter::iOL::COI;
	}
	else if (Interpreter::iOL::LC)
	{
		Interpreter::iOL::LC = false;
		runLoop(VariableList(INDEX, _vars), right);
	}
	else
	{
		if (!Interpreter::iOL::EI)
		{
			_vars[INDEX].value = right.value;
		}
		else
		{
			_vars[INDEX] = _vars[Interpreter::iOL::PRE_VC_I].variables[stoi(right.value)];
			Interpreter::iOL::EI = false;
		}
	}
}

bool InterpreterUtils::ol(int INDEX, std::vector<Variable> &_vars, Variable &right)
{
	//outstr("OLS nv:" + _vars[INDEX].value + " r:" + right.value);
	std::string tv = _vars[INDEX].value;
	if (_vars[INDEX].type == Variable::ValueType::Undefined)
	{
		_vars[INDEX].value = right.value;
		_vars[INDEX].type = right.type;
		return true;
	}
	else if (right.type == Variable::ValueType::String)
	{
		_vars[INDEX].type = Variable::ValueType::String;
		_vars[INDEX].value += right.value;
		return true;
	}

	if (_vars[INDEX].type == Variable::ValueType::Number) {
		float nr = std::stoi(right.value);
		float nv = std::stoi(_vars[INDEX].value);
		float nn = 0;
		nn = nv + (Interpreter::iOL::OP_A ? nr : (Interpreter::iOL::OP_M ? -nr : 0));
		nn = Interpreter::iOL::OP_T || Interpreter::iOL::OP_B ? 
			nv * (Interpreter::iOL::OP_T ? nr : (Interpreter::iOL::OP_B ? 1 / nr : 1))
			: nn;
		_vars[INDEX].value = VariableUtils::removeDec(std::to_string(nn));
	}
	else if (_vars[INDEX].type == Variable::ValueType::String)
	{
		float nr = std::stoi(right.value);
		_vars[INDEX].value = "";
		for (int i = 0; i < nr; i++)
		{
			_vars[INDEX].value += tv;
		}
	}

	//outstr("OL nv:" + _vars[INDEX].value + " r:" + right.value);

	bool tmp = Interpreter::iOL::OP_A ||
		Interpreter::iOL::OP_M ||
		Interpreter::iOL::OP_T ||
		Interpreter::iOL::OP_B;
	Interpreter::iOL::OP_A =
		Interpreter::iOL::OP_M =
		Interpreter::iOL::OP_T =
		Interpreter::iOL::OP_B = false;
	return tmp;
}

void InterpreterUtils::outstr(std::string out)
{
	std::cout << out << (Interpreter::iOL::NL ? "\n" : "");
}