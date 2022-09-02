#include <sstream>
#include "CInputValidator.h"
#include "CFileHandler.h"

static const std::string sOpen = "open";
static const std::string sConnect = "connect";
static const std::string sInit = "init";
static const std::string sOutput = "output";
static const std::string sStop = "stop";
static const std::string sRemove = "remove";
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

	if (std::find(moduleCmd.begin(), moduleCmd.end(), command) != moduleCmd.end())
	{
		if (command == sOpen)
		{
			std::string type = input->at(1);
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
		else if (command == sConnect)
		{
			if (isInteger(input->at(1)) && isInteger(input->at(2)))
			{
				return true;
			}
			else
			{
				displayError("Invalid arguments!");
				return false;
			}
		}
		else if (command == sInit || command == sOutput || command == sStop || command == sRemove)
		{
			if (isInteger(input->at(1)))
			{
				return true;
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
		<< "\t\t Help ----------------------------------------" << std::endl << std::endl
		<< "\t\t open \t\t -> \t This is a text for the open command" << std::endl
		<< "\t\t show \t\t -> \t This is a text for the show command" << std::endl
		<< "\t\t init \t\t -> \t This is a text for the init command" << std::endl
		<< "\t\t output \t\t -> \t This is a text for the output command" << std::endl
		<< "\t\t connect \t -> \t This is a text for the connect command" << std::endl
		<< "\t\t help \t\t -> \t This is a text for the help command" << std::endl
		<< "\t\t exit \t\t -> \t This is a text for the exit command" << std::endl << std::endl
		<< "\t\t ---------------------------------------------"
		<< std::endl;
}