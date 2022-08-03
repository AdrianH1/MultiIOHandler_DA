#include "stdafx.h"
#include <iostream>
//#include "IOHandler.h"
#include "CSocketHandler.h"
#include "CSerialHandler.h"
#include "CFileHandler.h"
#include "IIOModule.h"
//#include "Server.h"

std::vector<IIOModule*> modules;

//std::vector<std::thread*> asdf;
//std::thread* th2;

void createSocket(std::string ip, int unsigned port)
{
	std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
	CSocketHandler* socket = new CSocketHandler(ip, port);
	socket->run();
	modules.push_back(socket);
}

void createModule(std::string port, int bauderate)
{
	asio::io_service io_service;
	CSerialHandler* serial = new CSerialHandler(io_service, port, bauderate);
	modules.push_back(serial);
}

void createModule(std::string path)
{
	CFileHandler* file = new CFileHandler(path);
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


	//thr1.join();

	//while (true)
	//{
	//	std::cout << "wait";
	//	std::this_thread::sleep_for(std::chrono::seconds(10));
	//}

	//for (std::thread t : runningThreads)
	//{
	//	if (!nullptr)
	//		t->join();
	//}

	//for (std::thread* t : asdf)
	//{
	//	if (!nullptr)
	//		delete t;
	//}



	//t1.join(); //waiting for thread to finish before Main terminates
}