#include "stdafx.h"

class CUIHandler
{
public:
	CUIHandler() = default;
	std::vector<std::string> readInput();

private:
	std::vector<std::string> validCmd = { "open", "connect", "show" , "init", "output", "stop", "remove", "help", "exit" };

	bool inputValid(std::vector<std::string>*);
	std::vector<std::string> separateInput(std::string* inputLine);
	bool isInteger(const std::string s);
	void displayError(std::string);
	void displayHelp();
};
