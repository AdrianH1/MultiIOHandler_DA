#pragma once
#include "IOModule.h"

class CFile : public IIOModule
{
public:
	CFile() = default;
	CFile(std::string path);
	~CFile();
	int m_id;

private:
	std::string m_Path;
	void init();
	void send();
	void recv();
	void printInfo();
};