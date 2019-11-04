#pragma once
#include <vector>
#include <string>

using namespace std;
namespace Utility
{
	int convertCStringToNumber(const char* string);
	void safeDelete(void * ptr);
	void displayItemsInAVector(const std::vector<string> & vec);
	bool vectorContains(const std::vector<int> & vector, int num);
	bool fileExist(const string& path_to_file);
	string userConfirmation(string question);
}