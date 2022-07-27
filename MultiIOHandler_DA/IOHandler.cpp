#include "stdafx.h"
#include <iostream>
//#include "IOHandler.h"
#include "CSocket.h"
#include "CSerial.h"
#include "CFile.h"
#include "IIOModule.h"
//#include "Server.h"

std::vector<IIOModule*> modules;

void createModule(std::string ip, int unsigned port)
{
	asio::io_context io_context;
	CSocket* socket = new CSocket(io_context, ip, port);
	io_context.run();
	modules.push_back(socket);
}

void createModule()
{
	asio::io_context io_context;
	CSocket* socket = new CSocket(io_context);
	io_context.run();
	modules.push_back(socket);
}

void createModule(std::string port, int bauderate)
{
	asio::io_service io_service;
	CSerial* serial = new CSerial(io_service, port, bauderate);
	modules.push_back(serial);
}

void createModule(std::string path)
{
	CFile* file = new CFile(path);
	modules.push_back(file);
}

void init()
{

}

void connect(int id1, int id2)
{

}

void disconnect()
{

}

int main(int argc, char* argv[])
{
	//------Socket Test
	std::thread t1(static_cast<void(*)(std::string, int unsigned)>(createModule), "192.168.193.100", 65000);
	std::thread t3(static_cast<void(*)()>(createModule));

	//------Serial Test
	//std::thread t2(static_cast<void(*)(std::string, int)>(createModule), "COM1", 115200);

	for (int i = 0; i < 10; i++)
		std::cout << "test " << i << std::endl;



	for (IIOModule* m : modules)
	{
		m->printInfo();
	}

	t1.join(); //waiting for thread to finish before Main terminates
	//t2.join(); //waiting for thread to finish before Main terminates
	t3.join(); //waiting for thread to finish before Main terminates
}