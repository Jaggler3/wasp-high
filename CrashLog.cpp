#include "stdafx.h"
#include "CrashLog.h"

using namespace std;

std::string CrashLog::ad = "";

void CrashLog::Write(string data)
{
	ofstream f; f.open(".log");
	f << (ad += data + "\n");
	f.close();
}