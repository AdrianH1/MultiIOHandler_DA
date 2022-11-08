#pragma once
#include "stdafx.h"
#include "IIOModule.h"
#include "CInputValidator.h"

/**
 * This class is a handler for the console module
 * It inherits the IIOModule interface an overwrites all virtual functions
 * Console is a special module and most functions are empty
 */

class CConsoleHandler : public IIOModule
{
public:
	/**
	 * Constructor used to set Id and type
	 */
	CConsoleHandler();
	~CConsoleHandler();

	std::vector<std::string> readInput();

	//Not used
	void init();
	void stop();
	void output();

private:
	/**
	 * Writes message in parameter to the console (std::cout)
	 * Whole Function is locked with mutex
	 * If a filter is active it is applied before writing to device
	 */
	void write(std::vector<char> message);
	/**
	 * Print module information to console
	 */
	void printInfo();

	void read();

	std::string inputLine;
	std::vector<std::string> input;

	//Not used
	void connect();
	std::vector<std::string> getInfo();

	CInputValidator validator;
};


