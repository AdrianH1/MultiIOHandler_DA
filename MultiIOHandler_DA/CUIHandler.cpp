#include <sstream>
#include "CUIHandler.h"


std::vector<std::string> CUIHandler::readInput()
{
	std::string inputLine;


	std::cout << std::endl << ">>>";
	std::getline(std::cin, inputLine);

	std::vector<std::string> input = separateInput(&inputLine);

	if (inputValid(&input))
	{
		return input;
	}
	else
	{
		readInput();
	}
}

bool CUIHandler::inputValid(std::vector<std::string>* input)
{
	size_t argsCount = input->size() - 1;
	std::string command = input->at(0);
	asio::error_code ec;

	if (std::find(validCmd.begin(), validCmd.end(), command) != validCmd.end())
	{
		//Command open allows two arguments
		if (command == "open" && argsCount == 2)
		{
			asio::ip::address::from_string(input->at(1), ec);
			if (!ec)
			{
				if (atoi(input->at(2).c_str()) < 65535)
				{
					return true;
				}
			}
		}
		//Command init takes one argument
		else if (command == "init" && argsCount == 1)
		{
			if (!isInteger(input->at(1)))
			{
				return true;
			}
		}
		//Command output takes one argument
		else if (command == "output" && argsCount == 1)
		{
			if (!isInteger(input->at(1)))
			{
				return true;
			}
		}
		//Command show doesn't take arguments
		else if (command == "show" && argsCount == 0)
		{
			return true;
		}
		//Command connect....
		else if (command == "connect")
		{
			//to do
		}
		//Command help doesn't take arguments
		else if (command == "help" && argsCount == 0)
		{
			return true;
		}
		//Command exit doesn't take arguments
		else if (command == "exit" && argsCount == 0)
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


std::vector<std::string> CUIHandler::separateInput(std::string* inputLine)
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

bool CUIHandler::isInteger(const std::string s) {
	return s.find_first_not_of("0123456789") == std::string::npos;
}

void CUIHandler::displayError(std::string ec)
{
	std::cout << "ERROR: -----------------" << std::endl;
	std::cout << ec << std::endl;
	std::cout << "------------------------";
}

void CUIHandler::displayHelp()
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