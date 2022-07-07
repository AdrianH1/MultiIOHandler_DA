#pragma once

#include "IOModule.h"
#include <string>

class Socket : public IOModule
{
public:
	Socket() = default;
	Socket(std::string IP, int Port);
	~Socket();
	int m_id;

private:
	std::string m_IP;
	int m_Port;

	void init();
	void send();
	void recv();
};
