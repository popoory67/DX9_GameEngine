#include "CorePCH.h"
#include "Util.h"
#include "Log.h"

namespace Util
{
	bool ErrorMessage( const string& errorMessage )
	{
		return false;
	}

	string GetFileExtension(string& fileName)
	{
		string extension = fileName.substr(fileName.find_last_of(".") + 1);

		return extension;
	}

	string GetProjectPath()
	{
		char strBuffer[1024];

		string str = _getcwd(strBuffer, 1024);

		return str;
	}

	void PutLogMessage(const string& message)
	{
		Log::out << message + "\n";
		Log::Flush();
		std::ifstream(Log::path).rdbuf();
	}

}