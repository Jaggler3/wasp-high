#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Variable.h"
#include "VariableUtils.h"
#include "PlatformUtils.h"

class Artifacts
{
public:
	static std::vector<Variable> artifacts;
	static void Load(std::string filePath);
	static void Save(std::vector<Variable> a);
};
