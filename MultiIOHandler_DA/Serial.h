#pragma once
#include "IOModule.h"
#include <string>

class Serial : public IOModule
{
public:


	Serial() = default;
	Serial(std::string Port, int Speed);
	~Serial();

	int m_id;


private:
	void init();
	void send();
	void recv();

	std::string m_Port;
	int m_Speed;

};