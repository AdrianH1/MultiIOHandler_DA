#pragma once
#include "IIOModule.h"

class CFileHandler : public IIOModule
{
public:
	CFileHandler() = default;
	CFileHandler(std::string path);
	~CFileHandler();
	int m_id;
	void run();
	void stop();

private:
	std::string m_Path;
	void init();
	void write();
	void read();
	void printInfo();
};