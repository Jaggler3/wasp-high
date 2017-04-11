#pragma once

#include <string>
#include <iostream>
#include <fstream>

class CrashLog
{
private:
	static std::string ad;
public:
	static void Write(std::string data);
};

