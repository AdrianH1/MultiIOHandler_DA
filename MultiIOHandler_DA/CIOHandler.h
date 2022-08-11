#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CIOHandler
{
public:
	CIOHandler() = default;
	~CIOHandler();
	void callFunction(std::vector<std::string>* input);


private:
	std::vector<IIOModule*> modules;

	void createSocket(std::string ip, int unsigned port);
	void createSerial(std::string port, int bauderate);
	void createFile(std::string path);
	void connect(int id1, int id2);
	void disconnect();

};