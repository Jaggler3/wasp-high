#include "stdafx.h"
#include "VariableList.h"


VariableList::VariableList()
{
	this->index = -1;
	this->variables = std::vector<Variable>();
}

VariableList::VariableList(int index, std::vector<Variable> variables)
{
	this->index = index;
	this->variables = variables;
}

VariableList::~VariableList()
{

}
