#include "stdafx.h"

class CUIHandler
{
public:
	CUIHandler() = default;
	std::vector<std::string> readInput();

private:
	std::vector<std::string> validCmd = { "open", "connect", "show" , "help", "exit" };

	void callFunction(std::vector<std::string>*);
	bool inputValid(std::vector<std::string>*);
	std::vector<std::string> separateInput(std::string* inputLine);
	void displayError(std::string);
	void displayHelp();
};
