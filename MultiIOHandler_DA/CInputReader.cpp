#include "CInputReader.h"
#include "IIOModule.h"
#include <unordered_map>

std::vector<std::string> CInputReader::readInput()
{
	std::string inputLine;

	std::vector<std::string> input;
	//std::unordered_map<std::string, std::string> input;

	while (!inputValid(&input))
	{
		std::cout << std::endl << ">>>";
		std::getline(std::cin, inputLine);
		inputLine = lowerCase(inputLine);
		input = separateInput(&inputLine);
	}
	return input;
}

bool CInputReader::inputValid(std::vector<std::string>* input)
{
	if (input->size() == 0) { return false; }
	std::string command = input->at(0);
	//size_t paramCount = input->size();

	if (isCmdValid(&command))
	{
		if (std::find(openCmd.begin(), openCmd.end(), command) != openCmd.end())
		{
			//Command is 'open'
			std::string type;
			if (std::find(moduleTypes.begin(), moduleTypes.end(), type) != moduleTypes.end())
			{

			}
		}
		if (std::find(connectCmd.begin(), connectCmd.end(), command) != connectCmd.end())
		{ 
			//Command is 'connect'
		}
		if (std::find(moduleCmd.begin(), moduleCmd.end(), command) != moduleCmd.end())
		{ 
			//Command is 'init', 'output', 'input', 'stop', 'remove', 'filter'
		}
		if (std::find(jsonCmd.begin(), jsonCmd.end(), command) != jsonCmd.end())
		{ 
			//Command is 'save', 'load'
		}
		if (std::find(otherCmd.begin(), otherCmd.end(), command) != otherCmd.end())
		{ 
			//Command is 'show', 'help, 'exit'
		}
	}

	return false;
}

bool CInputReader::isCmdValid(std::string* command)
{
	std::vector<std::string> allCmd;
	allCmd.reserve(openCmd.size() + connectCmd.size() + moduleCmd.size() + jsonCmd.size() + otherCmd.size()); // preallocate memory
	allCmd.insert(allCmd.end(), openCmd.begin(), openCmd.end());
	allCmd.insert(allCmd.end(), connectCmd.begin(), connectCmd.end());
	allCmd.insert(allCmd.end(), moduleCmd.begin(), moduleCmd.end());
	allCmd.insert(allCmd.end(), jsonCmd.begin(), jsonCmd.end());
	allCmd.insert(allCmd.end(), otherCmd.begin(), otherCmd.end());

	if (std::find(allCmd.begin(), allCmd.end(), command) != allCmd.end())
	{
		return true;
	}
	return false;
}

bool CInputReader::isTypeValid(std::string* type)
{
	if (std::find(moduleTypes.begin(), moduleTypes.end(), type) != moduleTypes.end())
	{
		return true;
	}
	return false;
}

std::vector<std::string> CInputReader::setCmdParameter(std::vector<std::string>* input)
{
	return std::vector<std::string>();
}

std::vector<std::string> CInputReader::separateInput(std::string* inputLine)
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

std::unordered_map<std::string, std::string> CInputReader::mapInputToParam(std::vector<std::string>* input)
{
	std::unordered_map<std::string, std::string> commandMap;
	std::string action = input->at(0);

	if (std::find(openCmd.begin(), openCmd.end(), action) != openCmd.end())
	{
		//Action is 'open'
		std::string type = input->at(1);
		if (std::find(moduleTypes.begin(), moduleTypes.end(), type) != moduleTypes.end())
		{
			commandMap[typeParam] = type;
		}

		for (std::string param : typeToParamsMap.at(type))
		{
			for (int i = 2; i < input->size(); i + 2)
			{
				if (input->at(i) == param)
				{
					commandMap[param] = input->at(i);
				}
			}
		}
	}
	if (std::find(connectCmd.begin(), connectCmd.end(), action) != connectCmd.end())
	{
		//Action is 'connect'
	}
	if (std::find(moduleCmd.begin(), moduleCmd.end(), action) != moduleCmd.end())
	{
		//Action is 'init', 'output', 'input', 'stop', 'remove', 'filter'
	}
	if (std::find(jsonCmd.begin(), jsonCmd.end(), action) != jsonCmd.end())
	{
		//Action is 'save', 'load'
	}
	if (std::find(otherCmd.begin(), otherCmd.end(), action) != otherCmd.end())
	{
		//Action is 'show', 'help, 'exit'
	}

	return std::unordered_map<std::string, std::string>();
}


bool CInputReader::isInteger(const std::string s)
{
	return false;
}

std::string CInputReader::lowerCase(std::string inputline)
{
	return std::string();
}

void CInputReader::displayError(std::string ec)
{
}

void CInputReader::displayHelp()
{
}
