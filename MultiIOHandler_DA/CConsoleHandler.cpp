#include "CConsoleHandler.h"

static const std::string sStop = "stop";

CConsoleHandler::CConsoleHandler()
{
	setId(0);
	setModuleType(console);
    sendUserInput = true;
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

void CConsoleHandler::input()
{
    std::cout << "Sending Input from console to Module. Stop this mode by writing 'stop'" << std::endl;
    while (sendUserInput)
    {
        std::cout << std::endl << "Message: ";
        std::getline(std::cin, inputLine);
        if (inputLine == sStop)
        {
            sendUserInput = false;
            std::cout << "Sending console input to module stopped. Retrun to normal mode";
        }
        else
        {
            read();
        }
    }

    //Reset so input command can be executed again
    sendUserInput = true;
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
    std::vector<char> message(inputLine.begin(), inputLine.end());
    for (IIOModule* m : listenerTable)
    {
        m->write(message);
    }
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
