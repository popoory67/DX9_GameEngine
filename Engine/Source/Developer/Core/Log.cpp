#include "CorePCH.h"
#include "Log.h"
#include <ctime>

#pragma warning (disable : 4996)

namespace Log
{
	void Flush() 
	{ 
		out.flush(); 
	}

	string TimeStamp()
	{
		const auto now		= time(nullptr);
		char cstr[256]		{};

		return strftime(cstr, sizeof(cstr), "%Y%m%d_%H%M%S", localtime(&now)) ? cstr : "";
	}

	string PathToSessionLogFile()
	{
		static const string dir			= PROJECT_PATH;
		static const string fileName	= "log.txt";

		return dir + "/" + /*TimeStamp() + '_' +*/ fileName;
	}

	const string	path	= PathToSessionLogFile();
	ofstream		out		= ofstream(path);
}