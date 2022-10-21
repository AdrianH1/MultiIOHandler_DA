#pragma once
#include "stdafx.h"

/**
 * This interface gives every filter a default structure, functions and variables
 * Every filter has to inherit this interface
 */

class IDataFilter
{
public:
	//Id counter to ensure a unique id for every module
	static int m_idCounter;

	//Setters and Getters for all private member variables
	void setId(int id) { m_id = id; };
	const int getId() { return m_id; };
	void setName(std::string name) { m_name = name; };
	const std::string getName() { return m_name; };
	void setDesc(std::string desc) { m_desc = desc; };
	const std::string getDesc() { return m_desc; };

	/**
	* Virtual method that have to be overriden by all filter classes
	* Details to each override is described in the filter classes
	*/
	virtual std::string filterData(std::string message) = 0;

	/**
	 * Print filter information to console
	 */
	void printInfo() { std::cout << "ID: " << getId() << " | Name: " << getName() << " | Description: " << getDesc() << std::endl; }

private:
	//Id for unique identifier
	int m_id;
	//Name and description for each filter 
	std::string m_name;
	std::string m_desc;
};