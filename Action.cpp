#include "stdafx.h"
#include "Action.h"

Action::Action()
{
}

Action::Action(ActionType type, VariableData at, Variable ad)
{
	this->type = type;
	this->at = at;
	this->ad = ad;
}

Action Action::clone()
{
	return Action(type, at, ad);
}

Action::~Action()
{
}