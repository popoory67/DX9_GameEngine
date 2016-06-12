#pragma once

#include "CorePCH.h"

namespace Util
{
	bool Error(const string& errorMessage)
	{
		cout << "error : " << errorMessage << endl;
		return false;
	}
}