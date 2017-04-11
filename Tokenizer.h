#pragma once

#include <string>
#include <vector>
#include <regex>
#include <iostream>

class Tokenizer
{
public:
	class TokenData
	{
	public:
		std::vector<std::string> &tokens = std::vector<std::string>();
		std::vector<int> &lines = std::vector<int>();
		TokenData(std::vector<std::string> &tokens, std::vector<int> &lines);
		~TokenData();
	};
	static TokenData &t(std::string i);
};

