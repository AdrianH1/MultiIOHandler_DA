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

	enum type
	{
		console,
		serverSocket,
		clientSocket,
		file,
		serial
	};

	int m_id = 0;
	static int m_idCounter;
	type m_type;
	bool m_connected;

	
	std::vector<IIOModule*> listenerTable;

	static const size_t bufferMax = 50;
	static const size_t vBufferSize = 1 * 512;


		
private:
	

	
	
};
