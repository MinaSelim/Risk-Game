#include "Utility.h"

#include <sstream> 

int Utility::convertCStringToNumber(const char * string)
{
	int number = 0;
	std::stringstream stream(string);

	stream >> number;

	return number;
}
