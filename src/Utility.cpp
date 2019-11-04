#include "Utility.h"
#include <iostream>
#include <fstream>
#include <sstream> 


using namespace std;

int Utility::convertCStringToNumber(const char * string)
{
	int number = 0;
	std::stringstream stream(string);

	stream >> number;

	return number;
}

void Utility::safeDelete(void * ptr)
{
	if (ptr)
	{
		delete ptr;
	//	ptr = nullptr;
	}
		
}

void Utility::displayItemsInAVector(const std::vector<string> & vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << i << ". " << vec[i] << std::endl;
	}
}

bool Utility::vectorContains(const std::vector<int> & vector, int num)
{
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == num)
		{
			return true;
		}
	}

	return false;
}

string Utility::userConfirmation(string question)
{
	string userInput = "";
	do {
		cout << question << endl;
		cin >> userInput;
	} while (!userInput.compare("yes") == 0 && !userInput.compare("no") == 0);
	return userInput;
}

bool Utility::fileExist(const string& path_to_file)
{
	ifstream readFile;
	readFile.open(path_to_file);
	if (!readFile.is_open()) {
		return false;
	}
	else {
		readFile.close();
		return true;
	}
}