#include "stdafx.h"
#include <iostream>
#include "Masterhub.h"
#include "IOModule.h"
#include "Socket.h"
#include "Serial.h"

std::vector<IOModule> modules;

void createModule(Socket module)
{
	std::cout << "socket";
}

void createModule(Serial module)
{
	std::cout << "serial";
}



void connect(int id1, int id2)
{

}

void disconnect()
{

}

int main(int argc, char* argv[])
{
	Socket socket();
	Serial serial();

	

}