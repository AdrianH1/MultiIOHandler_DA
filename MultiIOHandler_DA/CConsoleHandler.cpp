#include "CConsoleHandler.h"

CConsoleHandler::CConsoleHandler()
{
	setId(0);
	setModuleType(console);
}

CConsoleHandler::~CConsoleHandler()
{
	stop();
}

void CConsoleHandler::init()
{

}

void CConsoleHandler::stop()
{
}

void CConsoleHandler::output()
{
}

void CConsoleHandler::write(std::string message)
{
	std::cout << message << std::endl;
}

void CConsoleHandler::read()
{
}

void CConsoleHandler::connect()
{
}

std::vector<std::string> CConsoleHandler::getInfo()
{
	return std::vector<std::string>();
}

void CConsoleHandler::printInfo()
{
}
