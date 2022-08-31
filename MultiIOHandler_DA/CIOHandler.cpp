#include "stdafx.h"
#include <iostream>
#include "CIOHandler.h"
#include "CClientSocketHandler.h"
#include "CServerSocketHandler.h"
#include "CSerialHandler.h"
#include "CFileHandler.h"
#include "IIOModule.h"
#include "CUIHandler.h"
#include "CJSONHandler.h"

bool running = true;

static const std::string sOpen = "open";
static const std::string sConnect = "connect";
static const std::string sInit = "init";
static const std::string sOutput = "output";
static const std::string sStop = "stop";
static const std::string sRemove = "remove";
static const std::string sShow = "show";
static const std::string sSave = "save";
static const std::string sLoad = "load";
static const std::string sExit = "exit";


void CIOHandler::createClientSocket(std::string ip, int unsigned port)
{
	CClientSocketHandler* socket = new CClientSocketHandler(ip, port);
	socket->init();
	modules.push_back(socket);
}

void CIOHandler::createServerSocket(int unsigned port)
{
	CServerSocketHandler* socket = new CServerSocketHandler(port);
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
}

void CIOHandler::showModules()
{
	if (modules.size() == 0)
	{
		std::cout << "No modules available!";
	}
	else
	{
		for (IIOModule* m : modules)
		{
			m->printInfo();
		}
	}
}

void CIOHandler::initModules(int id)
{
	for (IIOModule* m : modules)
	{
		if (m->getId() == id)
		{
			m->init();
			break;
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
}

void CIOHandler::saveJSON(std::string path)
{
	CJSONHandler json;
	json.save(path, modules);
}

void CIOHandler::loadJSON(std::string path)
{
	CJSONHandler json;
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
}

void CIOHandler::exitApp()
{
	for (IIOModule* m : modules)
	{
		m->stop();
	}
	running = false;
}


CIOHandler::~CIOHandler()
{
}

void CIOHandler::callFunction(std::vector<std::string>* input)
{
	if (input->at(0) == sOpen)
	{
		if (input->at(1) == "clientsocket")
		{
			createClientSocket(input->at(2), atoi(input->at(3).c_str()));
		}
		if (input->at(1) == "serversocket")
		{
			createServerSocket(atoi(input->at(2).c_str()));
		}
		else if (input->at(1) == "serial")
		{
			createSerial(input->at(2), atoi(input->at(3).c_str()));
		}
		else if (input->at(1) == "file")
		{
			createFile(input->at(2));
		}
	}
	else if (input->at(0) == sShow)
	{
		showModules();
	}
	else if (input->at(0) == sInit)
	{
		initModules(atoi(input->at(1).c_str()));
	}
	else if (input->at(0) == "output")
	{
		for (IIOModule* m : modules)
		{
			if (m->getId() == atoi(input->at(1).c_str()))
			{
				m->output();
				break;
			}
		}
	}
	else if (input->at(0) == sConnect)
	{
		connectModules(atoi(input->at(1).c_str()), atoi(input->at(2).c_str()));
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
	CUIHandler ui;

	while (running)
	{
		input = ui.readInput();
		IOHandler.callFunction(&input);
	}
}