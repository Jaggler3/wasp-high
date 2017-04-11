#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <iostream>

class PlatformUtils
{
public:
	static std::string executable_path;
	static void set_executable_path(std::string in);
	static std::string load_file(std::string path);
	static void save_file(std::string path, std::string data);
};

