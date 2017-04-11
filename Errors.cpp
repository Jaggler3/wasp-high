#include "stdafx.h"
#include "Errors.h"

using namespace std;

void Errors::exit(ErrorType type, string data, int line)
{
	switch (type)
	{
	VAR_UNDEF:
		cout << "Variable `" << data.c_str() << "' is undefined." << (line != -1 ? string(" (LINE " + line).append(")").c_str() : "") << endl;
	SET_TO_FUNC:
		cout << "Cannot set to specified object." << (line != -1 ? string(" (LINE " + line).append(")").c_str() : "") << endl;
	default:
	UNKNOWN:
		cout << "Unknown error has occured" << endl;
	}

	system("PAUSE");
	std::exit(0);
}