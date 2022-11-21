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

void CConsoleHandler::write(std::vector<char> message)
{
    //lock_guard to prevent simultaneous writing. Lock is released when block ends.
    const std::lock_guard<std::mutex> lock(writeMutex);
    if (filterIsSet())
    {
        std::vector<char> filteredMessage = getFilter()->filterData(message);
        for (char c : filteredMessage)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    else
    {
        for (char c : message)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

void CConsoleHandler::read()
{
}

void CConsoleHandler::connect()
{
}

std::vector<std::vector<std::string>> CConsoleHandler::getInfo()
{
	return std::vector<std::vector<std::string>>();
}

void CConsoleHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << "console" << std::endl;
}
