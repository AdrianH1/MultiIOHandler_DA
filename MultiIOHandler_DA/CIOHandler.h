#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CIOHandler
{
public:
	CIOHandler();
	~CIOHandler();
	void callFunction(std::vector<std::string>* input);

private:
	std::vector<IIOModule*> modules;

	void createConsole();
	void createClientSocket(std::string ip, int unsigned port);
	void createServerSocket(std::string ip, int unsigned port);
	void createSerial(std::string port, int bauderate);
	void createFile(std::string path);
	void connectModules(int id1, int id2);
	void showModules();
	void outputToConsole(int id);
	void initModules(int id);
	void removeModule(int id);
	void saveJSON(std::string path);
	void loadJSON(std::string path);
	void stopModule(int id);
	void exitApp();
};