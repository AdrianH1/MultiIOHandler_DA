#pragma once
#include "IIOModule.h"

class CFileHandler : public IIOModule
{
public:
	CFileHandler() = default;
	CFileHandler(std::string path);
	~CFileHandler();

	int m_id = -1;
	//void run();
	void stop();
	void init();
	void output();
	int getId();

private:
	std::string m_Path;
	std::fstream m_fs;

	bool writeToListener = false;
	bool outputToConsole = false;

	std::thread m_thrRead;
	std::thread m_thrOutput;

	void write(std::string message);
	void read();
	void connect();
	void printInfo();
};