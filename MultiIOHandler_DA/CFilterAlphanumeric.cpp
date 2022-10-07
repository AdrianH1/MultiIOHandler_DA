#include "CFilterAlphanumeric.h"
#include <cwctype>

CFilterAlphanumeric::CFilterAlphanumeric()
{
	setId(++m_idCounter);
	setName("Alphanumeric Filter");
	setDesc("Removes every character that is not alphanumeric");
}

std::vector<char> CFilterAlphanumeric::filterData(std::vector<char> message)
{
	std::vector<char> filteredMessage;
	for (char c : message)
	{
		/**
		* iswalnum is a standard library function found in <cwctype>
		* It returns true if the character is alphanumeric
		*/
		if (iswalnum(c))
		{
			filteredMessage.push_back(c);
		}
	}
	return filteredMessage;
}
