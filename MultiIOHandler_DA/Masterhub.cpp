#include "stdafx.h"
#include <iostream>
#include "Masterhub.h"
#include "Socket.h"
#include "Serial.h"
#include "File.h"
#include "Server.h"

#include <thread>

IOModule* createSocketModule(std::string ip, int port)
{
	Socket* socket = new Socket(ip, port);
	return socket;
}

IOModule* createSerialModule(std::string port, int speed)
{
	Serial* serial = new Serial(port, speed);
	return serial;
}

IOModule* createFileModule(std::string path)
{
	File* file = new File(path);
	return file;
}

void init()
{
	asio::io_context io_context;

	Server s(io_context, std::atoi("23"));

	io_context.run();
}


void connect(int id1, int id2)
{

}

void disconnect()
{

}

int main(int argc, char* argv[])
{
	std::thread th1(init);
	//init();

	for (int i = 0; i < 10; i++)
		std::cout << "test " << i << std::endl;

	th1.join(); //waiting for thread th1 to finish

	/*std::vector<IOModule*> modules;

	modules.push_back(createSocketModule("127.0.0.1", 123123));
	modules.push_back(createSerialModule("COM1", 115200));
	modules.push_back(createFileModule("C:/asdf/jkl/"));
	

	for (IOModule* m : modules)
	{
		m->printInfo();
	}*/

}