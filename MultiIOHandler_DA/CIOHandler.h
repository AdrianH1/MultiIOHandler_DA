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
	void createModule(std::string port, int bauderate);
	void createModule(std::string path);
	void connect(int id1, int id2);
	void disconnect();

};