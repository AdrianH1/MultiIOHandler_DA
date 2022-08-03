#include "stdafx.h"

class CUIHandler
{
public:
	CUIHandler() = default;

private:
	void readInput();
	bool inputValid(std::vector<std::string>);
	std::vector<std::string> separateInput(std::string inputLine);
	void displayError(std::string);
	void displayHelp();
};
