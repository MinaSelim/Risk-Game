#include "Utility.h"

#include <sstream> 
#include "Utility.h"

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
		delete ptr;
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
