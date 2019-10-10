#include "Utility.h"

#include <sstream> 
#include "..\inc\Utility.h"

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
