#pragma once
#include "IOModule.h"
#include <string>

class Serial : public IOModule
{
public:


	Serial() = default;
	Serial(int port, int speed);
	~Serial();

	int m_id;
	int m_Port;
	int m_Speed;

private:
	void init();
	void send();
	void recv();
	void printInfo();
};