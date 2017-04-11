#include "stdafx.h"
#include "Compiler.h"

using namespace std;

bool Compiler::CD::NV = false;
bool Compiler::CD::SV = false;

Action Compiler::CD::current_action = Action();

string Compiler::compile_script(Script script, Sequence &sequence)
{
	
	vector<string> symbols = script.symbols; if (symbols.size() == 0) { return ""; }
	vector<int> lines = script.lines;

	vector<Variable> artifacts;

	bool ca = false; //creating action

	vector<string> rsval = vector<string>();
	int vi = 0;
	VariableData &vd = VariableData();
	bool ecb = false;
	string fd = ""; //function data
	for (int i = 0; i < symbols.size(); i++)
	{
		string sym = symbols[i];
		cout << "SYM " << sym << endl;
		if (!ca)
		{
			CD::current_action = Action();
			if (sym == "var")
			{
				ca = true;
				CD::NV = true;
				CD::current_action.type = Action::ActionType::VAR_DEC;
				VariableData var = VariableData();
				sequence.variables.push_back(var);
			}
			else if(sym == "function")
			{
				ca = true;
				CD::NV = true;
				CD::current_action.type = Action::ActionType::FUNC_DEC;
				VariableData var = VariableData();
				sequence.variables.push_back(var);
			}
			else if ((vi = sequence.find_by_name(sym)) != -1)
			{
				vd = sequence.variables[vi];
				ca = true;
			}
			else if (sym == "print")
			{
				CD::current_action.type = Action::ActionType::PRINT;
				ca = true;
			}
		}
		else
		{
			if (CD::current_action.type == Action::ActionType::FUNC_DEC)
			{
				VariableData &lv = sequence.variables[sequence.variables.size() - 1];
				if (CD::NV)
				{
					lv.name = sym;
					CD::NV = false;
					CD::SV = true;
				}
				else if(CD::SV)
				{
					if (sym != "}" && !ecb)
					{
						if (sym == "=") { }
						else if (sym == "{") { ecb = (fd.length() != 0); }
						else if (sym == "%")
						{
							//get id of obj on right-side
						}
						else
						{
							fd += sym + " ";
							cout << "FD: " << fd << endl;
						}
					}
					else
					{
						CD::SV = false;
						lv.ref = VariableData::Reference::FUNC_EVAL;
						sequence.functions.push_back(Script(fd));
						lv.ref_index = sequence.functions.size() - 1;
						rsval.clear();
						CD::current_action.at = lv;
						sequence.actions.push_back(CD::current_action.clone());
						ca = false;
					}
				}
			}
			else if (CD::current_action.type == Action::ActionType::VAR_DEC)
			{
				VariableData &lv = sequence.variables[sequence.variables.size() - 1];
				if (CD::NV)
				{
					lv.name = sym;
					CD::NV = false;
					CD::SV = true;
				}
				else if (CD::SV)
				{
					if (sym != ";")
					{
						if (sym == "=") {}
						else if (sym == "%")
						{
							//get id of obj on right-side
						}
						else
						{
							rsval.push_back(sym);
						}
					}
					else
					{
						CD::SV = false;
						lv = sequence.evaluate(lv, rsval, artifacts);
						rsval.clear();
						CD::current_action.at = lv;
						sequence.actions.push_back(CD::current_action.clone());
						ca = false;
					}
				}
			}
			else if (CD::current_action.type == Action::ActionType::PRINT)
			{
				if (sym != ";")
				{
					if (sym == "=") { }
					else if (sym == "%")
					{
						//get id of obj on right-side
					}
					else
					{
						rsval.push_back(sym);
					}
				}
				else
				{
					VariableData &lv = VariableData();
					lv = sequence.evaluate(lv, rsval, artifacts);
					rsval.clear();
					CD::current_action.at = lv;
					sequence.actions.push_back(CD::current_action.clone());
					ca = false;
				}
			}
			else
			{
				if (sym == "--")
				{
					CD::current_action = Action(Action::ActionType::INT_DECR, vd, Variable());
					sequence.actions.push_back(CD::current_action.clone());
					ca = false;
				}
				else if (sym == "++")
				{
					CD::current_action = Action(Action::ActionType::INT_INCR, vd, Variable());
					sequence.actions.push_back(CD::current_action.clone());
					ca = false;
				}
				else if (sym == "=")
				{

				}
				else if (sym == ";")
				{

				}
			}
		}
	}

	Artifacts::Save(artifacts);
	
	if (sequence.actions.size() == 0) { return ""; }
	return sequence.format(script);
}

string Compiler::clean(string i)
{
	string script = i;
	int csi = 0;
	while ((csi = script.find("//", csi)) != -1) { script = script.substr(0, csi) + script.substr(script.find("\n", csi)); }
	csi = 0;
	while ((csi = script.find("/*", csi)) != -1)
	{
		int l = script.find("*/", csi) + 2;
		string nls = "";
		for (int k = csi; k < l; k++)
		{
			if (script[k] == '\n')
			{
				nls += '\n';
			}
		}
		script = script.substr(0, csi) + nls + script.substr(l);
	}
	return script;
} 