#include "stdafx.h"
#include <iostream>
#include "CIOHandler.h"
#include "CSocketHandler.h"
#include "CSerialHandler.h"
#include "CFileHandler.h"
#include "IIOModule.h"
#include "CUIHandler.h"

void CIOHandler::createSocket(std::string ip, int unsigned port)
{
	std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
	CSocketHandler* socket = new CSocketHandler(ip, port);
	socket->run();
	modules.push_back(socket);
}

void CIOHandler::createModule(std::string port, int bauderate)
{
	asio::io_service io_service;
	CSerialHandler* serial = new CSerialHandler(io_service, port, bauderate);
	modules.push_back(serial);
}

void CIOHandler::createModule(std::string path)
{
	CFileHandler* file = new CFileHandler(path);
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
		std::string ip = input->at(1);
		unsigned int port = atoi(input->at(2).c_str());
		createSocket(ip, port);
	}
	else if (input->at(0) == "show")
	{
		for (IIOModule* m : modules)
		{
			m->printInfo();
		}
	}
	else if (input->at(0) == "connect")
	{
	}
	else if (input->at(0) == "exit")
	{
	}
}

int main(int argc, char* argv[])
{
	CIOHandler IOHandler;

	bool running = true;
	std::vector<std::string> input;
	CUIHandler ui;

	while (running)
	{
		input = ui.readInput();
		IOHandler.callFunction(&input);
	}

	std::this_thread::sleep_for(std::chrono::seconds(60));

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