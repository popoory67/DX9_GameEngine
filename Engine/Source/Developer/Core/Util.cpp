#include "CorePCH.h"
#include "Util.h"


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
}