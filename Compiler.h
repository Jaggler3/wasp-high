#pragma once

#include <string>
#include <iostream>
#include <regex>
#include <vector>

#include "Sequence.h"
#include "Tokenizer.h"
#include "VariableData.h"
#include "Artifacts.h"
#include "Script.h"

class Sequence;

static class Compiler
{
public:
	static class CD
	{
	public:
		static Action current_action;
		static bool NV; //naming variable
		static bool SV; //setting variable
	};
	static std::string Compiler::compile_script(Script script, Sequence &sequence);
	static std::string clean(std::string script);
};
