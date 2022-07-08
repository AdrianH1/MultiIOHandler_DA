#include "stdafx.h"
#include <iostream>
#include "Masterhub.h"
#include "Socket.h"
#include "Serial.h"
#include "File.h"

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


void connect(int id1, int id2)
{

}

void disconnect()
{

}

int main(int argc, char* argv[])
{
	std::vector<IOModule*> modules;

	modules.push_back(createSocketModule("127.0.0.1", 123123));
	modules.push_back(createSerialModule("COM1", 115200));
	modules.push_back(createFileModule("C:/asdf/jkl/"));
	

	for (IOModule* m : modules)
	{
		m->printInfo();
	}

}