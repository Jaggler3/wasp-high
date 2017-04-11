#include "stdafx.h"
#include "Script.h"

using namespace std;


Script::Script()
{
	this->symbols = vector<string>();
	this->lines = vector<int>();
}

Script::Script(string script)
{
	Tokenizer::TokenData td = Tokenizer::t(script);
	this->symbols = td.tokens;
	this->lines = td.lines;
}


Script::~Script()
{

}