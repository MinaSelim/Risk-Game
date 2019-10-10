#pragma once
#include <vector>
namespace Utility
{
	int convertCStringToNumber(const char* string);
	void safeDelete(void * ptr);
	bool vectorContains(const std::vector<int> & vector, int num);
}