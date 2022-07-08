#pragma once
#include "IOModule.h"

class File : public IOModule
{
public:
	File() = default;
	File(std::string path);
	~File();
	int m_id;

private:
	std::string m_Path;
	void init();
	void send();
	void recv();
	void printInfo();
};