#include "stdafx.h"
#include "CIOHandler.h"
#include "CConsoleHandler.h"
#include "CClientSocketHandler.h"
#include "CServerSocketHandler.h"
#include "CClientSocketHandlerUDP.h"
#include "CServerSocketHandlerUDP.h"
#include "CSerialHandler.h"
#include "CFileHandler.h"
#include "IIOModule.h"
//#include "CInputValidator.h"
#include "CKonfigJSON.h"
#include "CFilterAlphanumeric.h"

//Boolean for endless while loop unti user runs "exit" command
bool running = true;

static const std::string sOpen = "open";
static const std::string sConnect = "connect";
static const std::string sInit = "init";
static const std::string sOutput = "output";
static const std::string sStop = "stop";
static const std::string sRemove = "remove";
static const std::string sFilter = "filter";
static const std::string sShow = "show";
static const std::string sSave = "save";
static const std::string sLoad = "load";
static const std::string sExit = "exit";

static const std::string sServerSocket = "serversocket";
static const std::string sClientSocket = "clientsocket";
static const std::string sServerSocketUDP = "serversocketudp";
static const std::string sClientSocketUDP = "clientsocketudp";
static const std::string sFile = "file";
static const std::string sSerial = "serial";

CIOHandler::CIOHandler()
{
	//Console Module and Filter are created beforehand and not via user input
	createConsole();
	createFilter();
}

CIOHandler::~CIOHandler()
{
}

void CIOHandler::createFilter()
{
	CFilterAlphanumeric* filterAlpha = new CFilterAlphanumeric();
	filter.push_back(filterAlpha);
}

void CIOHandler::createConsole()
{
	CConsoleHandler* console = new CConsoleHandler();
	modules.push_back(console);
}

void CIOHandler::createClientSocket(std::string ip, int unsigned port)
{
	CClientSocketHandler* socket = new CClientSocketHandler(ip, port);
	socket->init();
	modules.push_back(socket);
}

void CIOHandler::createServerSocket(std::string ip, int unsigned port)
{
	CServerSocketHandler* socket = new CServerSocketHandler(ip, port);
	socket->init();
	modules.push_back(socket);
}

void CIOHandler::createClientSocketUDP(std::string ip, int unsigned port)
{
	CClientSocketHandlerUDP* socket = new CClientSocketHandlerUDP(ip, port);
	socket->init();
	modules.push_back(socket);
}

void CIOHandler::createServerSocketUDP(std::string ip, int unsigned port)
{
	CServerSocketHandlerUDP* socket = new CServerSocketHandlerUDP(ip, port);
	socket->init();
	modules.push_back(socket);
}

void CIOHandler::createSerial(std::string port, int bauderate)
{
	CSerialHandler* serial = new CSerialHandler(port, bauderate);
	serial->init();
	modules.push_back(serial);
}

void CIOHandler::createFile(std::string path)
{
	CFileHandler* file = new CFileHandler(path);
	file->init();
	modules.push_back(file);
}

void CIOHandler::connectModules(int id1, int id2)
{
	//Search for first id and add a pointer of second id to its listener table
	IIOModule* first{};
	for (IIOModule* m : modules)
	{
		if (m->getId() == id1)
		{
			first = m;
		}
	}
	for (IIOModule* m : modules)
	{
		if (m->getId() == id2 && first != nullptr)
		{
			first->listenerTable.push_back(m);
			first->connect();
		}
	}
	std::cout << "Modules connected!" << std::endl;
}

void CIOHandler::showModules()
{
	std::cout << "Modules: " << std::endl;
	{
		for (IIOModule* m : modules)
		{
			m->printInfo();
		}
	}
}

void CIOHandler::showFilter()
{
	std::cout <<std ::endl << "Filter: " << std::endl;
	for (IDataFilter* f : filter)
	{
		f->printInfo();
	}
}

void CIOHandler::outputToConsole(int id)
{
	for (IIOModule* m : modules)
	{
		if (m->getId() == id)
		{

			if (m->getConnectedState())
			{
				m->listenerTable.push_back(modules.at(0));
				m->output();
				break;
			}
			else
			{
				std::cout << "Module not connected!" << std::endl;
			}
		}
	}
}

void CIOHandler::initModules(int id)
{
	for (IIOModule* m : modules)
	{
		if (m->getId() == id)
		{
			if (m->getConnectedState())
			{
				std::cout << "Already initialized!" << std::endl;
			}
			else
			{
				m->init();
				break;	
			}
		}
	}
}

void CIOHandler::removeModule(int id)
{
	for (int i = 0; i < modules.size(); i++)
	{
		if (modules.at(i)->getId() == id)
		{
			delete modules.at(1);
			modules.erase(modules.begin() + i);
			break;
		}
	}
	std::cout << "Module removed!" << std::endl;
}

void CIOHandler::addFilter(int moduleId, int filterId)
{
	for (IIOModule* m : modules)
	{
		if (m->getId() == moduleId)
		{
			for (IDataFilter* f : filter)
			{
				if (f->getId() == filterId)
				{
					m->setFilter(f);
					break;
				}
			}
		}
	}
	std::cout << "Filter added!" << std::endl;
}

void CIOHandler::saveJSON(std::string path)
{
	CKonfigJSON json;
	json.save(path, modules);
}

void CIOHandler::loadJSON(std::string path)
{
	CKonfigJSON json;
	json.load(path, modules);
}

void CIOHandler::stopModule(int id)
{
	for (IIOModule* m : modules)
	{
		if (m->getId() == id)
		{
			m->stop();
			break;
		}
	}
	std::cout << "Module stopped!" << std::endl;
}

void CIOHandler::exitApp()
{
	for (IIOModule* m : modules)
	{
		m->stop();
	}
	for (IIOModule* m : modules)
	{
		delete m;
	}
	running = false;
}

//First string is always the command
void CIOHandler::callFunction(std::vector<std::string>* input)
{
	if (input->at(0) == sOpen)
	{
		//Second string is always the module if the command is open
		if (input->at(1) == sClientSocket && input->size() == 4)
		{
			createClientSocket(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == sServerSocket && input->size() == 4)
		{
			createServerSocket(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == sClientSocketUDP && input->size() == 4)
		{
			createClientSocketUDP(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == sServerSocketUDP && input->size() == 4)
		{
			createServerSocketUDP(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == sSerial && input->size() == 4)
		{
			createSerial(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == sFile && input->size() == 3)
		{
			createFile(input->at(2));
		}
	}
	else if (input->at(0) == sShow)
	{
		showModules();
		showFilter();
	}
	else if (input->at(0) == sInit)
	{
		//Second string is a module id
		initModules(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sOutput)
	{
		//Second string is a module id
		outputToConsole(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sConnect)
	{
		//Second and third string is a module id
		connectModules(atoi(input->at(1).c_str()), atoi(input->at(2).c_str()));
	}
	else if (input->at(0) == sFilter)
	{
		//Second string is a module id. Third string is a filter id
		addFilter(atoi(input->at(1).c_str()), atoi(input->at(2).c_str()));
	}
	else if (input->at(0) == sRemove)
	{
		//Second string is a module id
		removeModule(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sSave)
	{
		//Second string is a file path
		saveJSON(input->at(1));
	}
	else if (input->at(0) == sLoad)
	{
		//Second string is a file path
		loadJSON(input->at(1));
	}
	else if (input->at(0) == sStop)
	{
		//Second string is a module id
		stopModule(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sExit)
	{
		exitApp();
	}
}

int main(int argc, char* argv[])
{

	CIOHandler IOHandler;

	CConsoleHandler* console = static_cast<CConsoleHandler*>(IOHandler.modules.at(0));

	std::vector<std::string> input;
	//CInputValidator ui;

	//Endless loop until user runs "exit" command
	while (running)
	{
		input = console->readInput();
		IOHandler.callFunction(&input);
	}
}