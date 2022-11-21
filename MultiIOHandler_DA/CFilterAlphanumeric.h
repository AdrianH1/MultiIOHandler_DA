#pragma once
#include "stdafx.h"
#include "IDataFilter.h"

class CFilterAlphanumeric : public IDataFilter
{
public:
	/**
	 * Constructor used set id, name and description
	 */
	CFilterAlphanumeric();

	/**
	 * Filters data given in parameter
	 * Removes every not alphanumeric character from message
	 * 
	 * @params - String which is read from device/file/serial
	 * @return - A filtered string without alphanumeric characters
	 */
	std::vector<char> filterData(std::vector<char> message) override;
};