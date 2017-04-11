#pragma once

#include <vector>
#include <string>
#include <random>

class Variable
{
private:
	static std::string genID();
public:
	enum ValueType {
		String,
		Number,
		Function,
		Boolean,
		Array,
		Undefined
	};
	std::vector<Variable> variables = std::vector<Variable>();
	std::string apID = "";
	std::string ID;
	std::string value = "";
	ValueType type = ValueType::Undefined;
	Variable();
	Variable(std::string value, ValueType type);
	~Variable();
};

