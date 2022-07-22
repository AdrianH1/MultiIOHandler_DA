#pragma once
#include "stdafx.h"



class IOModule
{
public:

	//virtual void init() = 0;
	virtual void send() = 0;
	virtual void recv() = 0;
	virtual void printInfo() = 0;
	static int m_idCounter;

private:
	std::vector<IOModule*> ListenerTable;
	
};
