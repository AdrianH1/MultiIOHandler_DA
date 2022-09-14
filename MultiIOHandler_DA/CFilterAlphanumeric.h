#pragma once
#include "stdafx.h"
#include "IDataFilter.h"

class CFilterAlphanumeric : public IDataFilter
{
public:
	CFilterAlphanumeric();
	std::string filterData(std::string message);
};