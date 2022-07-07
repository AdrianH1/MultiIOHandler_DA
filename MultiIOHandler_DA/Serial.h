#pragma once
#include "IOModule.h"
#include <string>

class Serial : public IOModule
{
public:
	std::string Port;
	int Speed;

private:
	void init();
	void send();
	void recv();

};