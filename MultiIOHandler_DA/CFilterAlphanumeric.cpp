#include "CFilterAlphanumeric.h"
#include <cwctype>

CFilterAlphanumeric::CFilterAlphanumeric()
{
	setId(++m_idCounter);
	setName("Alphanumeric Filter");
	setDesc("Removes every character that is not alphanumeric");
}

std::string CFilterAlphanumeric::filterData(std::string message)
{
	std::string filteredMessage;
	for (char c : message)
	{
		if (iswalnum(c))
		{
			filteredMessage += c;
		}
	}
	return filteredMessage;
}
