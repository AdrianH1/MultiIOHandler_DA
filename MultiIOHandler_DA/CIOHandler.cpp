#include "stdafx.h"
#include <iostream>
#include "CIOHandler.h"
#include "CConsoleHandler.h"
#include "CClientSocketHandler.h"
#include "CServerSocketHandler.h"
#include "CSerialHandler.h"
#include "CFileHandler.h"
#include "IIOModule.h"
#include "CInputValidator.h"
#include "CKonfigJSON.h"
#include "CFilterAlphanumeric.h"

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
static const std::string sFile = "file";
static const std::string sSerial = "serial";

CIOHandler::CIOHandler()
{
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
	std::cout << "Modules saved!" << std::endl;
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
	running = false;
}


void CIOHandler::callFunction(std::vector<std::string>* input)
{
	if (input->at(0) == sOpen)
	{
		if (input->at(1) == sClientSocket && input->size() == 4)
		{
			createClientSocket(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == sServerSocket && input->size() == 4)
		{
			createServerSocket(input->at(2), atoi(input->at(3).c_str()));
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
		initModules(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sOutput)
	{
		outputToConsole(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sConnect)
	{
		connectModules(atoi(input->at(1).c_str()), atoi(input->at(2).c_str()));
	}
	else if (input->at(0) == sFilter)
	{
		addFilter(atoi(input->at(1).c_str()), atoi(input->at(2).c_str()));
	}
	else if (input->at(0) == sRemove)
	{
		removeModule(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == sSave)
	{
		saveJSON(input->at(1));
	}
	else if (input->at(0) == sLoad)
	{
		loadJSON(input->at(1));
	}
	else if (input->at(0) == sStop)
	{
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

	std::vector<std::string> input;
	CInputValidator ui;

	while (running)
	{
		input = ui.readInput();
		IOHandler.callFunction(&input);
	}
}