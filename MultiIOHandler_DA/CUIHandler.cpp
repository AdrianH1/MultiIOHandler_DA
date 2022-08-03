#include "CUIHandler.h"


void CUIHandler::readInput()
{
	std::string inputLine;
	bool running = true;

	while (running)
	{
		std::cout << std::endl << ">>>";
		std::getline(std::cin, inputLine);

		std::vector<std::string> input = separateInput(inputLine);

		if (inputValid(input))
		{

		}

	}

}

bool CUIHandler::inputValid(std::vector<std::string> input)
{
	std::vector<std::string> valid = { "open", "connect", "show" , "exit" };
	int argsCount = input.size() - 1;
	std::string command = input.at(0);
	asio::error_code ec;

	if (std::find(valid.begin(), valid.end(), command) != valid.end())
	{
		//Command open allows two arguments
		if (command == "open" && argsCount == 2)
		{
			asio::ip::address::from_string(input.at(1), ec);
			if (!ec)
			{

			}
			//Check if arguments are valid
		}
		else if (command == "show")
		{
		}
		else if (command == "connect")
		{
		}
		else if (command == "exit")
		{
		}
	}
	else
	{
		displayError("Invalid command or invalid amount of arguments!");
		return false;
	}
}

std::vector<std::string> CUIHandler::separateInput(std::string inputLine)
{
	std::vector<std::string> input;
	std::string temp = "";
	bool firstWord = true;

	for (char c : inputLine)
	{
		if (c == ' ')
		{
			input.push_back(temp);
			temp = "";
		}
		temp += c;
	}
	return input;
}

void CUIHandler::displayError(std::string ec)
{
	std::cout << "ERROR: -----------------" << std::endl;
	std::cout << ec << std::endl;
	std::cout << "------------------------";
}

void CUIHandler::displayHelp()
{
}