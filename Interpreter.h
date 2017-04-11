#pragma once

#include <string>
#include "Variable.h"
#include "VariableList.h"
#include "InterpreterUtils.h"
#include "Artifacts.h"
#include "CrashLog.h"
#include "CompilerUtils.h"

class Interpreter
{
public:
	static Variable GetGlobal(int index);
	static const std::string globals[];
	static void execute(std::string input);
	static VariableList e(std::string i, VariableList &l);
	static class iOL
	{
	public:
		static bool RS;				//right side
		static bool PRNT;			//print
		static bool OP_A;			//addition
		static bool OP_M;			//minus (subtraction)
		static bool OP_D;			//distance (sub abs)
		static bool OP_T;			//times (multiplication)
		static bool OP_B;			//break (division)
		static bool IDG;			//ID get
		static bool COI;			//close out if
		static bool HI;				//has if
		static bool SI;				//starting if
		static bool FI;				//false if
		static bool FC;				//function call
		static bool NL;				//new line
		static bool LC;				//expecting loop condition
		static bool EI;				//expecting (array) index
		static std::string LD;		//loop data
		static std::string LCD;		//loop condition data
		static std::string Debug();
		static int PRE_VC_I;		//previous variable index before creation
	};
};

