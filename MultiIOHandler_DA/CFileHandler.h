#pragma once
#include "IIOModule.h"

class CFileHandler : public IIOModule
{
public:
	CFileHandler() = default;
	CFileHandler(std::string path);
	~CFileHandler();
	int m_id;

private:
	std::string m_Path;
	void init();
	void write();
	void read();
	void printInfo();
};