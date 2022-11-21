#pragma once
#include "stdafx.h"
#include "IIOModule.h"

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

	//Not used
	void init() override;
	void stop() override;
	void output() override;

	/**
	 * Reads and saves user input and calls read() Method
	 */
	void input();

private:

	std::string inputLine;
	bool sendUserInput;

	/**
	 * Writes message in parameter to the console (std::cout)
	 * Whole Function is locked with mutex
	 * If a filter is active it is applied before writing to device
	 */
	void write(std::vector<char> message) override;
	/**
	 * Print module information to console
	 */
	void printInfo() override;

	/**
	 * Forwards read user input to modules in listener table
	 */
	void read() override;

	//not used
	void connect() override;

	std::vector<std::vector<std::string>> getInfo();

};


