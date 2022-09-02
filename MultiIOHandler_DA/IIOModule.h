#pragma once
#include "stdafx.h"



class IIOModule
{
public:

	virtual void init() = 0;
	virtual void stop() = 0;
	virtual void write(std::string message) = 0;
	virtual void read() = 0;
	virtual void connect() = 0;
	virtual void output() = 0;
	virtual std::vector<std::string> getInfo() = 0;
	virtual void printInfo() = 0;

	int getId() { return m_id; };

	static int m_idCounter;
	int m_id = 0;
	std::vector<IIOModule*> listenerTable;

	enum type
	{
		console,
		serverSocket,
		clientSocket,
		file,
		serial
	};

	type m_type;
private:
	
};
