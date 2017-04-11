// WaspCompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "Interpreter.h"
#include "Artifacts.h"
#include "PlatformUtils.h"
#include "Compiler.h"

using namespace std;

int main(int argc, char* args[])
{
	PlatformUtils::set_executable_path(args[0]);

	string sp = PlatformUtils::executable_path + '\\' + string(args[1]) + ".ws";
	string bp = PlatformUtils::executable_path + '\\' + string(args[1]) + ".wsb";
	string ip = PlatformUtils::load_file(sp);
	string op = Compiler::compile_script(Script(ip), Sequence());
	PlatformUtils::save_file(bp, op);

	Artifacts::Load("artifacts.wa");

	if (argc == 2)
	{
		//Interpreter::execute(PlatformUtils::load_file(bp));
		system("PAUSE");
	}
	else
	{
		string input = "";
		while (cin >> input)
		{
			Interpreter::execute(input);
		}
	}
	

    return 0;
}
