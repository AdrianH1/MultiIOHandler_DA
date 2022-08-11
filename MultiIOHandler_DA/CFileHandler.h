#pragma once
#include "IIOModule.h"

class CFileHandler : public IIOModule
{
public:
	CFileHandler() = default;
	CFileHandler(std::string path);
	~CFileHandler();

	int m_id;
	//void run();
	void stop();
	void init();
	void output();
	int getId();

private:
	std::string m_Path;
	std::fstream m_fs;

	void write(std::string message);
	void read();
	void connect();
	void printInfo();
};