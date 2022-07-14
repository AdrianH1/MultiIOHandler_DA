#pragma once

#include "stdafx.h"
#include "IOModule.h"
#include "Server.h"

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
	void init(std::string ip, int port);
	void send();
	void recv();
	void printInfo();
};
