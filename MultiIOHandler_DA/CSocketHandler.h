#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CSocketHandler : public IIOModule
{
public:
	CSocketHandler() = default;
	CSocketHandler(std::string ip, int unsigned port);
	~CSocketHandler();
	int m_id = -1;
	void run();
	void stop();
	void init();
	void output();
	int getId();

private:
	std::string m_ip;
	int unsigned m_port;

	void read();
	void write();
	void printInfo();
	void accept();
	void getData();

	std::vector<char> vBuffer;
	std::vector <std::string> readBuffer;
	asio::io_context m_context;
	asio::ip::tcp::socket m_socket;
	std::thread m_thrContext;

	//enum { max_length = 1024 };
	//char data[max_length];
};
