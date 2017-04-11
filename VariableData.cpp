#include "stdafx.h"
#include "VariableData.h"


VariableData::VariableData()
{
	this->name = "undefined";
	this->ref = Reference::NONE;
	this->ref_index = -1;
}


VariableData::~VariableData()
{
}
