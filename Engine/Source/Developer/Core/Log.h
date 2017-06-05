#pragma once

#include <fstream>

namespace Log
{
	extern const string		path;
	extern ofstream			out;

	void		Flush();
}