#include "stdafx.h"
#include "PlatformUtils.h"

using namespace std;

string PlatformUtils::executable_path = "";

void PlatformUtils::set_executable_path(std::string in)
{
	string _p = string(in);
	const int DIR_MAX_PATH = 1024;
	wchar_t buffer[DIR_MAX_PATH];
	GetModuleFileName(NULL, buffer, DIR_MAX_PATH);
	wstring ws = wstring(buffer);
	string path = string(ws.begin(), ws.end());
	int i = path.length(); for (; i != 0; i--) { if (path[i] == '\\') { break; } }
	string np = "";  for (int j = 0; j < i; j++) { np += path[j]; }
	PlatformUtils::executable_path = np;
}

string PlatformUtils::load_file(string path)
{
	string res = "";
	ifstream f(path);
	ostringstream output;
	output << f.rdbuf();
	res = output.str();
	f.close();
	return res;
}

void PlatformUtils::save_file(std::string path, std::string data)
{
	ofstream f(path, ofstream::out | ofstream::trunc);
	f << data;
	f.close();
}
