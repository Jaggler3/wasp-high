#include "stdafx.h"
#include "Sequence.h"

using namespace std;

VariableData Sequence::evaluate(VariableData &res, vector<string> data, vector<Variable> &artifacts, int line)
{
	string oper = "";
	int vi = 0;
	for (int i = 0; i < data.size(); i++)
	{
		//check for if operator first
		//...
		//then check if it is a number
		if (CompilerUtils::is_float(data[i]))
		{
			if (oper == "")
			{
				if (res.ref == VariableData::Reference::NONE)
				{
					res.ref = VariableData::Reference::ARTIFACT;
					//check if artifact already exists?
					//...
					Variable v = Variable();
					v.value = data[i];
					v.type = Variable::ValueType::Number;
					artifacts.push_back(v);

					res.ref_index = artifacts.size() - 1;
				}
			}
		}
		else if((vi = find_by_name(data[i])) != -1)
		{
			if (oper == "")
			{
				res = variables[vi];
			}
		}
	}
	
	return res;
}

Sequence::Sequence()
{
	this->actions = vector<Action>();
	this->variables = vector<VariableData>();
	this->functions = vector<Script>();
}


Sequence::~Sequence()
{
}

int Sequence::find_by_name(string name)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

string Sequence::format(Script script)
{
	string res = "";
	int _index = -1;
	for (int i = 0; i < actions.size(); i++)
	{
		Action a = actions[i];
		if (a.type == Action::ActionType::VAR_DEC)
		{
			res += ";>";

			if (a.at.ref == VariableData::Reference::ARTIFACT)
			{
				res += "_" + to_string(a.at.ref_index) + "|";
			}
			else if (a.at.ref == VariableData::Reference::CELL)
			{
				res += "[" + to_string(a.at.ref_index) + "]";
			}

			_index++;
		}
		else if (a.type == Action::ActionType::FUNC_DEC)
		{
			res += ";>(" + Compiler::compile_script(functions[a.at.ref_index], clear_actions()) + ")";
		}
		else if (a.type == Action::ActionType::INT_DECR)
		{
			int ni = find_by_name(a.at.name);
			if (ni != -1 && ni != _index)
			{
				res += "[" + to_string(ni) + "]";
				_index = ni;
			}
			res += "$-";
		}
		else if (a.type == Action::ActionType::INT_INCR)
		{
			int ni = find_by_name(a.at.name);
			if (ni != -1 && ni != _index)
			{
				res += "[" + to_string(ni) + "]";
				_index = ni;
			}
			res += "$+";
		}
	}
	return res;
}

Sequence& Sequence::clear_actions()
{
	Sequence &s = Sequence(*this);
	s.actions = vector<Action>();
	return *this;
}