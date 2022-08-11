#include "stdafx.h"

class CUIHandler
{
public:
	CUIHandler() = default;
	std::vector<std::string> readInput();

private:
	std::vector<std::string> validCmd = { "open", "connect", "show" , "init", "output", "stop", "remove", "help", "exit" };
	std::vector<std::string> validModules = { "socket", "file", "serial" };

	bool inputValid(std::vector<std::string>*);
	std::vector<std::string> separateInput(std::string* inputLine);
	bool isInteger(const std::string s);
	std::string lowerCase(std::string inputline);
	void displayError(std::string);
	void displayHelp();
};
