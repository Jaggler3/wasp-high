#include "stdafx.h"
#include "Tokenizer.h"

using namespace std;

Tokenizer::TokenData &Tokenizer::t(string in)
{
	vector<string> symbols = vector<string>();
	vector<int> lines = vector<int>();

	regex rgx("\\d+\\.?\\d*|\\+=|\\-=|\\--|\\*=|\\/=|\\==|\\++|\\w+\\.\\w+|\\w+\\:\\w+|\\w+|\\<=?|\\=|[^\s\"']|\\\"([^\"]*)\\\" | '([^'] * )");
	
	for (sregex_iterator it(in.begin(), in.end(), rgx), it_end; it != it_end; ++it)
	{
		string s = (*it)[0];
		if (!(s == " " || s == "\n" || s == "\t" || s == "\r"))
		{
			symbols.push_back(s);
			int lc = 0;
			int np = -1;
			int j = 0;
			for (j = 0; j < (*it).position(0); j += (np = in.find('\n', j) != -1 ? np : 1)) {}
		}
	}

	return Tokenizer::TokenData(symbols, lines);
}

Tokenizer::TokenData::TokenData(vector<string> &tokens, vector<int> &lines)
{
	this->tokens = tokens;
	this->lines = lines;
}

Tokenizer::TokenData::~TokenData()
{

}