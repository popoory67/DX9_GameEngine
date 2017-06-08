#pragma once


namespace Util
{
	bool		ErrorMessage( const string& errorMessage );

	string		GetFileExtension(string& fileName);

	string		GetProjectPath();

	void		PutLogMessage(const string& message);
}