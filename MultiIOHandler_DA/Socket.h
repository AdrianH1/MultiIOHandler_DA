#pragma once

#include "IOModule.h"

class Socket : public IOModule
{
public:
	Socket() = default;
	Socket(std::string ip, int port);
	~Socket();
	int m_id;

private:
	std::string m_IP;
	int m_Port;
	void init();
	void send();
	void recv();
	void printInfo();
};
