#include "stdafx.h"

/**
 * This class is responsible for reading user input and validating it.
 * It contains a readInput() function which reads the user input.
 */

class CInputValidator
{
public:
	CInputValidator() = default;

	/**
	 * Reads a complete line of user input and validates it
	 * Separates the line by space and stores them in a vector
	 *
	 * @return - A string vector of every input separated by a space
	 */
	std::vector<std::string> readInput();

private:
	/**
	 * Valid commands and module types used for validation
	 */
	std::vector<std::string> moduleCmd = { "open", "connect", "init", "output", "stop", "remove", "filter"};
	std::vector<std::string> otherCmd = { "show", "save", "load", "help", "exit" };
	std::vector<std::string> validModuleTypes = { "clientsocket", "serversocket", "file", "serial" };

	/**
	 * Validates user input for correct command, modul type and argument count 
	 *
	 * @params - String vector of separated user input by space
	 * @return - A boolean depending on the validity of command, modul type and argument count
	 */
	bool inputValid(std::vector<std::string>* input);

	/**
	 * Separates a line of input by space for further usage
	 *
	 * @params - Whole line of input as one string
	 * @return - A string vector with the separated string given in the parameters
	 */
	std::vector<std::string> separateInput(std::string* inputLine);

	/**
	 * Check if a string is an integer 
	 */
	bool isInteger(const std::string s);

	/**
	 * Converts all input into lowercase to support lower and uppercase user input
	 */
	std::string lowerCase(std::string inputline);

	/**
	 * Function to output an error. 
	 * This is used so that all error outputs look the same.
	 */
	void displayError(std::string ec);

	/**
	 * Displays the full help text in the console
	 */
	void displayHelp();
};
