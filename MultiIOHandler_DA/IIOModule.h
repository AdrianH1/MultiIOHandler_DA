#pragma once
#include "stdafx.h"



class IIOModule
{
public:

	virtual void init() = 0;
	virtual void run() = 0;
	virtual void stop() = 0;
	virtual void write() = 0;
	virtual void read() = 0;
	virtual void printInfo() = 0;
	static int m_idCounter;

private:
	std::vector<IIOModule*> ListenerTable;
	
};
