#pragma once
#include <vector>
#include <string>

using namespace std;
namespace Utility
{
	int convertCStringToNumber(const char* string);
	void safeDelete(void * ptr);
	bool vectorContains(const std::vector<int> & vector, int num);
	string userConfirmation(string question);
}