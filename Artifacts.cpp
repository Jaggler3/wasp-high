#include "stdafx.h"
#include "Artifacts.h"

using namespace std;

std::vector<Variable> Artifacts::artifacts = std::vector<Variable>();

void Artifacts::Load(string filePath)
{
	//... load file line by line into variables list
	ifstream f(PlatformUtils::executable_path + '\\' + filePath);
	for (string line; getline(f, line);)
	{
		Variable v = Variable();
		if (VariableUtils::endsWith(line, string("num")))
		{
			v.type = Variable::ValueType::Number;
		} else if(VariableUtils::endsWith(line, string("string")))
		{
			v.type = Variable::ValueType::String;
		}

		v.value = VariableUtils::valueOf(line);
		Artifacts::artifacts.push_back(v);
	}
}

void Artifacts::Save(std::vector<Variable> a)
{
	std::string data = "";
	for (int i = 0; i < a.size(); i++)
	{
		data += a[i].value + "," +
			(a[i].type == Variable::Number ? "num" : a[i].type == Variable::String ? "string" : "boolean") + 
			(i != a.size() - 1 ? "\n" : "");
	}
	PlatformUtils::save_file(PlatformUtils::executable_path + "\\artifacts.wa", data);
}
