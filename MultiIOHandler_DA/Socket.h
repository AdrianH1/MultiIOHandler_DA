#pragma once

#include "IOModule.h"
#include <string>

class Socket : public IOModule
{
public:
	std::string IP;
	int Port;

private:
	void init();
	void send();
	void recv();

};
