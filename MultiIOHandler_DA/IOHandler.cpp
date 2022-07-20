#include "stdafx.h"
#include <iostream>
//#include "IOHandler.h"
#include "Socket.h"
#include "Serial.h"
#include "File.h"
#include "Server.h"

std::vector<IOModule*> modules;

void createModule(std::string ip, int unsigned port)
{
	Socket* socket = new Socket(ip, port);
	modules.push_back(socket);
}

void createModule(int port, int speed)
{
	Serial* serial = new Serial(port, speed);
	modules.push_back(serial);
}

void createModule(std::string path)
{
	File* file = new File(path);
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
	//createModule("192.168.193.100", 23);

	std::thread t1(static_cast<void(*)(std::string, int unsigned)>(createModule), "192.168.193.100", 65000);
	t1.join(); //waiting for thread t1 to finish before Main terminates

	for (int i = 0; i < 10; i++)
		std::cout << "test " << i << std::endl;

	/*std::vector<IOModule*> modules;

	modules.push_back(createSocketModule("127.0.0.1", 123123));
	modules.push_back(createSerialModule("COM1", 115200));
	modules.push_back(createFileModule("C:/asdf/jkl/"));
	*/

	for (IOModule* m : modules)
	{
		m->printInfo();
	}

}