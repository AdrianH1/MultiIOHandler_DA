#include <sstream>
#include "CUIHandler.h"


std::vector<std::string> CUIHandler::readInput()
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

bool CUIHandler::inputValid(std::vector<std::string>* input)
{
	if (input->size() == 0) { return false; }
	size_t argsCount = input->size() - 1;
	std::string command = input->at(0);
	asio::error_code ec;

	if (std::find(validCmd.begin(), validCmd.end(), command) != validCmd.end())
	{
		//Command open allows three arguments
		if (command == "open" && argsCount == 3)
		{
			std::string type = input->at(1);
			if (std::find(validCmd.begin(), validCmd.end(), type) != validCmd.end())
			{
				if (type == "socket")
				{
					asio::ip::address::from_string(input->at(1), ec);
					if (!ec)
					{
						if (atoi(input->at(2).c_str()) < 65535)
						{
							return true;
						}
						else
						{
							displayError("Invalid Port!");
							return false;
						}
					}
				}
				else if (type == "serial")
				{

				}
				else if (type == "file")
				{
					std::ifstream file(input->at(2));
					if (file)
					{
						return true;
					}
					else
					{
						displayError("File does not exist!");
						return false;
					}
				}

			}
		}
		//Command init takes one argument
		else if (command == "init" && argsCount == 1)
		{
			if (isInteger(input->at(1)))
			{
				return true;
			}
			else
			{
				displayError("Invalid ID!");
				return false;
			}
		}
		//Command output takes one argument
		else if (command == "output" && argsCount == 1)
		{
			if (isInteger(input->at(1)))
			{
				return true;
			}
			else
			{
				displayError("Invalid ID!");
				return false;
			}
		}
		//Command show doesn't take arguments
		else if (command == "show" && argsCount == 0)
		{
			return true;
		}
		//Command connect takes two argument
		else if (command == "connect" && argsCount == 2)
		{
			if (isInteger(input->at(1)) && isInteger(input->at(2)))
			{
				return true;
			}
			else
			{
				displayError("Invalid IDs!");
				return false;
			}
		}
		//Command stop doesn't take arguments
		else if (command == "stop" && argsCount == 0)
		{
			return true;
		}
		//Command remove takes one argument
		else if (command == "remove" && argsCount == 1)
		{
			if (isInteger(input->at(1)))
			{
				return true;
			}
			else
			{
				displayError("Invalid ID!");
				return false;
			}
		}
		//Command help doesn't take arguments
		else if (command == "help" && argsCount == 0)
		{
			displayHelp();
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

std::string CUIHandler::lowerCase(std::string inputline)
{
	std::string result = "";
	for (char c : inputline)
	{
		result += std::tolower(c);
	}
	return result;
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