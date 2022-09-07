#pragma once
#include "IIOModule.h"

class CFileHandler : public IIOModule
{
public:
	CFileHandler() = default;
	CFileHandler(std::string path);
	~CFileHandler();

	void stop();
	void init();
	void output();

private:
	std::string m_path;
	std::fstream m_fs;

	bool writeToListener = false;
	bool reading = true;

	std::thread m_thrRead;
	std::thread m_thrOutput;

	void write(std::string message);
	void read();
	void connect();
	std::vector<std::string> getInfo();
	void printInfo();
};