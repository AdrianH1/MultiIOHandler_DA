#pragma once
#include "stdafx.h"
#include "IIOModule.h"

class CConsoleHandler : public IIOModule
{
public:
	CConsoleHandler();
	~CConsoleHandler();

	void init();
	void stop();
	void output();

private:
	void write(std::string message);
	void read();
	void connect();
	std::vector<std::string> getInfo();
	void printInfo();

};


