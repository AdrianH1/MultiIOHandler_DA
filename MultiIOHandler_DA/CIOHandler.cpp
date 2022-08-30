#include "stdafx.h"
#include <iostream>
#include "CIOHandler.h"
#include "CClientSocketHandler.h"
#include "CSerialHandler.h"
#include "CFileHandler.h"
#include "IIOModule.h"
#include "CUIHandler.h"
#include "CJSONHandler.h"

bool running = true;

void CIOHandler::createSocket(std::string ip, int unsigned port)
{
	CClientSocketHandler* socket = new CClientSocketHandler(ip, port);
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

void CIOHandler::connect(int id1, int id2)
{

}

void CIOHandler::disconnect()
{

}

CIOHandler::~CIOHandler()
{
}

void CIOHandler::callFunction(std::vector<std::string>* input)
{
	if (input->at(0) == "open")
	{
		if (input->at(1) == "clientsocket")
		{
			std::string ip = input->at(2);
			unsigned int port = atoi(input->at(3).c_str());
			createSocket(ip, port);
		}
		else if (input->at(1) == "serial")
		{
			std::string port = input->at(2);
			int baudrate = atoi(input->at(3).c_str());
			createSerial(port, baudrate);
		}
		else if (input->at(1) == "file")
		{
			std::string path = input->at(2);
			createFile(path);
		}
	}
	else if (input->at(0) == "show")
	{
		for (IIOModule* m : modules)
		{
			m->printInfo();
		}
	}
	else if (input->at(0) == "init")
	{
		for (IIOModule* m : modules)
		{
			if (m->getId() == atoi(input->at(1).c_str()))
			{
				m->init();
				break;
			}
		}
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
	else if (input->at(0) == "connect")
	{
		IIOModule* first{};
		for (IIOModule* m : modules)
		{
			if (m->getId() == atoi(input->at(1).c_str()))
			{
				first = m;
			}
		}
		for (IIOModule* m : modules)
		{
			if (m->getId() == atoi(input->at(2).c_str()) && first != nullptr)
			{
				first->listenerTable.push_back(m);
				first->connect();
			}
		}
	}
	else if (input->at(0) == "remove")
	{
		for (int i = 0; i < modules.size(); i++)
		{
			if (modules.at(i)->getId() == atoi(input->at(1).c_str()))
			{
				modules.erase(modules.begin()+i);
				break;
			}
		}
	}
	else if (input->at(0) == "save")
	{
		CJSONHandler json;
		json.save(input->at(1), modules);
	}
	else if (input->at(0) == "load")
	{
		CJSONHandler json;
		json.load(input->at(1), modules);
	}
	else if (input->at(0) == "stop")
	{
		for (IIOModule* m : modules)
		{
			m->stop();
		}
	}
	else if (input->at(0) == "exit")
	{
		for (IIOModule* m : modules)
		{
			m->stop();
		}
		running = false;
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

	//std::this_thread::sleep_for(std::chrono::seconds(10));

	/*
	//------Socket Test
	createSocket("192.168.0.218", 65123);
	//std::thread t1(static_cast<void(*)(std::string, int unsigned)>(createSocket), "192.168.193.100", 65000);
	//th2->detach();

	std::cout << "thread id: " << std::this_thread::get_id() << std::endl;

	//------Serial Test
	//std::thread t2(static_cast<void(*)(std::string, int)>(createModule), "COM1", 115200);

	for (int i = 0; i < 10; i++)
		std::cout << "test " << i << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(60));

	for (IIOModule* m : modules)
	{
		m->stop();
	}
	*/
}