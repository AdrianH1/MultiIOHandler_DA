#include "stdafx.h"
#include <iostream>
#include "Masterhub.h"
#include "Socket.h"
#include "Serial.h"

std::vector<IOModule*> modules;

void createModule(Socket module)
{
	std::cout << "socket " << module.m_id << std::endl;
}

void createModule(Serial module)
{
	std::cout << "serial " << module.m_id << std::endl;
}



void connect(int id1, int id2)
{

}

void disconnect()
{

}

int main(int argc, char* argv[])
{
	Socket socket("127.0.0.1", 123123);
	Serial serial("COM1", 115200);

	createModule(socket);
	createModule(serial);

	

}