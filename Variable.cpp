#include "stdafx.h"
#include "Variable.h"

using namespace std;

string Variable::genID()
{
	char* alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	string res = "0x";
	for (int i = 0; i < 6; i++)
	{
		res += alph[rand() % strlen(alph)];
	}

	return res;
}

Variable::Variable()
{
	this->ID = genID();
}

Variable::Variable(std::string value, ValueType type)
{
	this->ID = genID();
	this->value = value;
	this->type = type;
}


Variable::~Variable()
{

}
