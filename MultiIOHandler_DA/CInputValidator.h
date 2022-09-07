#include "stdafx.h"

class CInputValidator
{
public:
	CInputValidator() = default;
	std::vector<std::string> readInput();

private:
	std::vector<std::string> moduleCmd = { "open", "connect", "init", "output", "stop", "remove"};
	std::vector<std::string> otherCmd = { "show", "save", "load", "help", "exit" };
	std::vector<std::string> validModuleTypes = { "clientsocket", "serversocket", "file", "serial" };

	bool inputValid(std::vector<std::string>* input);
	std::vector<std::string> separateInput(std::string* inputLine);
	bool isInteger(const std::string s);
	std::string lowerCase(std::string inputline);
	void displayError(std::string ec);
	void displayHelp();
};
