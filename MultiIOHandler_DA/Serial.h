#pragma once
#include "IOModule.h"
#include <string>

class Serial : public IOModule
{
public:


	Serial() = default;
	Serial(std::string port, int speed);
	~Serial();

	int m_id;
	std::string m_Port;
	int m_Speed;

private:
	void init();
	void send();
	void recv();
	void printInfo();
};