#pragma once
#include "stdafx.h"



class IIOModule
{
public:

	virtual void init() = 0;
	//virtual void run() = 0;
	virtual void stop() = 0;
	virtual void write(std::string message) = 0;
	virtual void read() = 0;
	virtual void connect() = 0;
	virtual void output() = 0;
	virtual int getId() = 0;
	virtual std::vector<std::string> getInfo() = 0;
	virtual void printInfo() = 0;
	static int m_idCounter;
	std::vector<IIOModule*> listenerTable;

	/*Type
	1 -> Socket TCP
	2 -> Socket UDP
	3 -> File
	4 -> Serial
	*/
	int m_type;
private:
	
};
