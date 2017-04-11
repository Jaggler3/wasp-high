#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>

using namespace std;

bool Interpreter::iOL::RS = false;
bool Interpreter::iOL::PRNT = false;
bool Interpreter::iOL::OP_A = false;
bool Interpreter::iOL::OP_M = false;
bool Interpreter::iOL::OP_D = false;
bool Interpreter::iOL::OP_T = false;
bool Interpreter::iOL::OP_B = false;
bool Interpreter::iOL::COI = false;
bool Interpreter::iOL::IDG = false;
bool Interpreter::iOL::HI = false;
bool Interpreter::iOL::SI = false;
bool Interpreter::iOL::FI = false;
bool Interpreter::iOL::FC = false;
bool Interpreter::iOL::NL = true;
bool Interpreter::iOL::LC = false;
bool Interpreter::iOL::EI = false;
string Interpreter::iOL::LD = "";
string Interpreter::iOL::LCD = "";
int Interpreter::iOL::PRE_VC_I = -1;

string Interpreter::iOL::Debug()
{
	return to_string(Interpreter::iOL::RS) + ", " +
		to_string(Interpreter::iOL::PRNT) + ", " +
		to_string(Interpreter::iOL::OP_A) + ", " +
		to_string(Interpreter::iOL::OP_M) + ", " +
		to_string(Interpreter::iOL::OP_D) + ", " +
		to_string(Interpreter::iOL::OP_T) + ", " +
		to_string(Interpreter::iOL::OP_B) + ", " +
		to_string(Interpreter::iOL::COI) + ", " +
		to_string(Interpreter::iOL::IDG) + ", " +
		to_string(Interpreter::iOL::HI) + ", " +
		to_string(Interpreter::iOL::SI) + ", " +
		to_string(Interpreter::iOL::FI) + ", " +
		to_string(Interpreter::iOL::NL) + ", " +
		to_string(Interpreter::iOL::LC) + ", " +
		to_string(Interpreter::iOL::FC) + ", " +
		to_string(Interpreter::iOL::EI)
		;
}

const string Interpreter::globals[] = {
	"true", "Boolean",
	"false", "Boolean",
	"0", "Number",
	"1", "Number",
	"10", "Number",
	" ", "String",
	"\n", "String",
};

Variable Interpreter::GetGlobal(int index)
{
	Variable v = Variable();
	v.value = Interpreter::globals[index * 2];
	string type = Interpreter::globals[index * 2 + 1];
	if (type == "Boolean")
	{
		v.type = Variable::ValueType::Boolean;
	}
	else if (type == "Number")
	{
		v.type = Variable::ValueType::Number;
	}
	else if (type == "String")
	{
		v.type = Variable::ValueType::String;
	}
	else if (type == "Function")
	{
		v.type = Variable::ValueType::Function;
	}

	return v;
}

void Interpreter::execute(string input)
{
	e(input, VariableList());
}

VariableList Interpreter::e(string s, VariableList &l)
{
	int INDEX = l.index;
	vector<Variable> _vars = l.variables;

	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		char c = s[i];
		//cout << std::string("[" + std::to_string(i) + "]:{" + to_string(INDEX) + "}\t" + Interpreter::iOL::Debug()) << endl;
		CrashLog::Write(std::string("[" + std::to_string(i) + "]:(" + c + "):{" + to_string(INDEX) + "}\t" + Interpreter::iOL::Debug()));

		if (iOL::COI && c != '#') { continue; }
		if (c == '?') { INDEX = 0; continue; }
		if (c == '/' && s[i + 1] == '/') { return VariableList(INDEX, _vars); } //exit / comment start
		else if (c == '/') {  //restart
			VariableList nvl = e(s, VariableList(INDEX, _vars));
			INDEX = nvl.index;
			_vars = nvl.variables;
		}
		else if (c == '`')
		{
			if (s[i + 1] == '`')
			{
				i++;
			}
			else
			{
				iOL::EI = true;
			}
		}
		else if (c == 'A')
		{
			_vars[INDEX].type = Variable::ValueType::Array;
			iOL::RS = false;
		}
		else if (c == '^')
		{
			iOL::LD = "";
			for (int start = 1; start < s.length() - i; i++)
			{
				char sis = s[i + start];
				if (sis != '|') { iOL::LD += sis; }
				else { i += start; break; }
			}

			iOL::LC = true;
		}
		else if (c == '#')
		{
			iOL::COI = iOL::HI ? false : iOL::COI;
			if (!iOL::HI)
			{
				if (s[i + 1] == '#') //not
				{
					iOL::FI = true;
					i++;
				}
				iOL::SI = true;
				iOL::HI = true;
			} else
			{
				iOL::HI = false;
			}
		}
		else if (c == ';')
		{
			if (s[i + 1] == '>') //create new variable
			{
				Variable nv = Variable();
				_vars.push_back(nv);
				iOL::RS = true;
				INDEX = _vars.size() - 1;
				i++;
			} else if(s[i + 1] == '<')
			{
				_vars.pop_back();
				INDEX--;
				i++;
			}
		}
		else if (c == '@') //accessing a global
		{
			string ID = "";
			for (int start = 1; start < s.length() - i; i++)
			{
				char sis = s[i + start];
				if (sis != '|') { ID += sis; }
				else { i += start; break; }
			}
			auto ov = GetGlobal(std::stoi(ID));
			InterpreterUtils::operation(INDEX, _vars, ov);
			iOL::RS = false;
		}
		else if (c == '_') //accessing an artifact
		{
			string ID = "";
			for (int start = 1; start < s.length() - i; i++)
			{
				char sis = s[i + start];
				if (sis != '|') { ID += sis; }
				else { i += start; break; }
			}
			auto ov = Artifacts::artifacts[std::stoi(ID)];
			InterpreterUtils::operation(INDEX, _vars, ov);
			iOL::RS = false;
		}
		else if (c == '$')
		{
			if (iOL::FC)
			{
				iOL::FC = false;
				VariableList nvl = e(_vars[INDEX].value, VariableList(INDEX, _vars));
				INDEX = nvl.index;
				_vars = nvl.variables;
			} 
			else if(iOL::RS)
			{
				Variable ov;
				if (iOL::IDG)
				{
					ov.value = _vars[INDEX].ID;
					ov.type = Variable::ValueType::String;
					iOL::IDG = false;
				} else
				{
					ov = _vars[INDEX];
				}
				InterpreterUtils::operation(INDEX, _vars, ov);
			} 
			else
			{
				if (iOL::IDG)
				{
					auto ov = Variable(_vars[INDEX].ID, Variable::ValueType::String);
					InterpreterUtils::operation(INDEX, _vars, ov);
					iOL::IDG = false;
				}
				else
				{
					iOL::RS = true;
				}
			}
		}
		else if (c == '+')
		{
			bool e = s[i + 1] == '+';
			iOL::RS = iOL::OP_A = e;
			i += iOL::OP_A ? 1 : 0;
			if (!e && _vars[INDEX].type == Variable::ValueType::Number)
			{
				_vars[INDEX].value = to_string(stoi(_vars[INDEX].value) + 1);
			}
		}
		else if (c == '-')
		{
			bool e = s[i + 1] == '-';
			iOL::RS = iOL::OP_M = e;
			i += iOL::OP_M ? 1 : 0;
			if (!e && _vars[INDEX].type == Variable::ValueType::Number)
			{
				_vars[INDEX].value = to_string(stoi(_vars[INDEX].value) - 1);
			}
		}
		else if (c == '\'')
		{
			iOL::RS = iOL::OP_T = true;
		}
		else if (c == '"' || c == '\"')
		{
			iOL::RS = iOL::OP_B = true;
		}
		else if (c == '~' || c == '~')
		{
			iOL::RS = iOL::OP_D = true;
		}
		else if (c == '!')
		{
			iOL::RS = iOL::PRNT = true;
			iOL::NL = s[i + 1] != '!';
			i += iOL::NL ? 0 : 1;
		}
		else if (c == '[')
		{
			int amt = 0;
			string as = "";
			while (i <= s.length())
			{
				i++;
				if (s[i] != ']')
				{
					as += s[i];
				}
				else
				{
					if (CompilerUtils::is_float(as))
					{
						amt = -INDEX + stoi(as);
					}
					else
					{
						int leftc = 0, rightc = 0;
						for (int p = 0; p < as.size(); p++) { if (as[p] == '<') { leftc--; } else if (as[p] == '>') { rightc++; } }
						amt = leftc + rightc;
					}
					if (iOL::FC)
					{
						iOL::FC = false;
						VariableList nvl = e(_vars[INDEX + amt].value, VariableList(INDEX, _vars));
						INDEX = nvl.index;
						_vars = nvl.variables;
					}
					else if (iOL::LC)
					{
						iOL::LC = false;
						InterpreterUtils::runLoop(VariableList(INDEX, _vars), _vars[INDEX + amt]);
					}
					else if (iOL::OP_D && !iOL::SI)
					{
						_vars[INDEX].value = string("" + (stoi(_vars[INDEX].value) - stoi(_vars[INDEX + amt].value)));
						iOL::RS = iOL::OP_D = false;
					}
					else if (iOL::OP_D || iOL::OP_T || iOL::OP_M || iOL::OP_A || iOL::OP_B)
					{
						InterpreterUtils::operation(INDEX, _vars, _vars[INDEX + amt]);
					}
					else
					{
						iOL::PRE_VC_I = INDEX;
						INDEX += amt;
					}
					break;
				}
			}
		}
		else if (c == '%')
		{
			iOL::IDG = true;
		}
		else if (c == '(')
		{
			int ee = s.find(')', i);
			i++;
			string func = s.substr(i, ee - i);
			i = ee;
			_vars[INDEX].value = func;
			_vars[INDEX].type = Variable::ValueType::Function;
			iOL::RS = false;
		}
		else if (c == '*') { iOL::FC = true;
		}
	}

	for (int i = 0; i < _vars.size(); i++)
	{
		CrashLog::Write("VAL " + to_string(i) + "=" + _vars[i].value);
	}

	return VariableList(INDEX, _vars);
}