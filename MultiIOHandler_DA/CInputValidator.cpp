#include <sstream>
#include "CInputValidator.h"
#include "CFileHandler.h"

static const std::string sOpen = "open";
static const std::string sConnect = "connect";
static const std::string sInit = "init";
static const std::string sOutput = "output";
static const std::string sInput = "input";
static const std::string sStop = "stop";
static const std::string sRemove = "remove";
static const std::string sFilter = "filter";
static const std::string sHelp = "help";

std::vector<std::string> CInputValidator::readInput()
{
	std::string inputLine;

	std::vector<std::string> input;

	while (!inputValid(&input))
	{
		std::cout << std::endl << ">>>";
		std::getline(std::cin, inputLine);
		inputLine = lowerCase(inputLine);
		input = separateInput(&inputLine);
	}
	return input;
}

bool CInputValidator::inputValid(std::vector<std::string>* input)
{
	if (input->size() == 0) { return false; }
	std::string command = input->at(0);
	size_t argsCount = input->size();

	//Search if the given command is part of the moduleCmd vector and therefore is a valid command
	if (std::find(moduleCmd.begin(), moduleCmd.end(), command) != moduleCmd.end())
	{
		if (command == sOpen)
		{
			std::string type = input->at(1);
			//Search if the given type is part of the validModuleTypes vector and therefore is a valid type
			if (std::find(validModuleTypes.begin(), validModuleTypes.end(), type) != validModuleTypes.end())
			{
				return true;
			}
			else
			{
				displayError("Invalid module type!");
				return false;
			}
		}
		else if (command == sConnect || command == sFilter)
		{
			if (argsCount == 3)
			{
				if (isInteger(input->at(1)) && isInteger(input->at(2)))
				{
					return true;
				}
				return false;
			}
			else
			{
				displayError("Invalid arguments!");
				return false;
			}
		}
		else if (command == sInit || command == sOutput || command == sInput || command == sStop || command == sRemove)
		{
			if (argsCount == 2)
			{
				if (isInteger(input->at(1)))
				{
					return true;
				}
				return false;
			}
			else
			{
				displayError("Invalid arguments!");
				return false;
			}
		}
		else
		{
			displayError("Invalid command!");
			return false;
		}
	}
	else if (std::find(otherCmd.begin(), otherCmd.end(), command) != otherCmd.end())
	{
		if (command == sHelp)
		{
			displayHelp();
			return false;
		}
		return true;
	}
	else
	{
		displayError("Invalid command!");
		return false;
	}
}

std::vector<std::string> CInputValidator::separateInput(std::string* inputLine)
{
	std::vector<std::string> input;
	std::stringstream ss(*inputLine);
	std::string word;

	while (ss >> word)
	{
		input.push_back(word);
	}

	return input;
}

bool CInputValidator::isInteger(const std::string s) {
	return s.find_first_not_of("0123456789") == std::string::npos;
}

std::string CInputValidator::lowerCase(std::string inputline)
{
	std::string result = "";
	for (char c : inputline)
	{
		result += std::tolower(c);
	}
	return result;
}

void CInputValidator::displayError(std::string ec)
{
	std::cout << "ERROR: -----------------" << std::endl;
	std::cout << ec << std::endl;
	std::cout << "------------------------";
}

void CInputValidator::displayHelp()
{
	std::cout
		<< "\t Help ----------------------------------------" << std::endl
		<< std::endl << "\t open \t\t -> \t Creates an IO Module." << std::endl
		<< "\t\t\t\t Parameters are different for each module type:" << std::endl
		<< "\t\t\t\t serversocket: IP Port" << std::endl
		<< "\t\t\t\t clientsocket: IP Port" << std::endl
		<< "\t\t\t\t file: Path" << std::endl
		<< "\t\t\t\t serial: Port baudrate" << std::endl << std::endl
		<< "\t\t\t\t Example for clientsocket:" << std::endl
		<< "\t\t\t\t open clientsocket 127.0.0.1 65123" << std::endl
		<< std::endl << "\t show \t\t -> \t Displays all modules" << std::endl
		<< "\t\t\t\t This command has no parameters" << std::endl
		<< std::endl << "\t init \t\t -> \t Initializes a Module" << std::endl
		<< "\t\t\t\t This command takes an ID as a Parameter" << std::endl << std::endl
		<< "\t\t\t\t Example to initialize module with ID 3:" << std::endl
		<< "\t\t\t\t init 3" << std::endl
		<< std::endl << "\t output \t -> \t Writes data of a module to console" << std::endl
		<< "\t\t\t\t This command takes an ID as a Parameter" << std::endl << std::endl
		<< "\t\t\t\t Example to write data from module with ID 5 to console:" << std::endl
		<< "\t\t\t\t output 5" << std::endl
		<< std::endl << "\t connect \t -> \t Connects two modules unidirectional" << std::endl
		<< "\t\t\t\t This command takes two IDs as a Parameters" << std::endl << std::endl
		<< "\t\t\t\t Example to connect write data from module 1 to module 4:" << std::endl
		<< "\t\t\t\t connect 1 4" << std::endl
		<< std::endl << "\t stop \t\t -> \t Stop any connection or output for a module" << std::endl
		<< "\t\t\t\t This command takes an ID as a Parameter" << std::endl << std::endl
		<< "\t\t\t\t Example to write data from module with ID 3 to console:" << std::endl
		<< "\t\t\t\t stop 3" << std::endl
		<< std::endl << "\t remove \t -> \t Removes a module" << std::endl
		<< "\t\t\t\t This command takes an ID as a Parameter" << std::endl << std::endl
		<< "\t\t\t\t Example to write data from module with ID 6 to console:" << std::endl
		<< "\t\t\t\t remove 6" << std::endl
		<< std::endl << "\t help \t\t -> \t Displays this help" << std::endl
		<< std::endl << "\t exit \t\t -> \t Exit the application" << std::endl << std::endl
		<< "\t ---------------------------------------------"
		<< std::endl;
}