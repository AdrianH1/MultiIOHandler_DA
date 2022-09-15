#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CClientSocketHandler : public IIOModule
{
public:
	CClientSocketHandler() = default;
	CClientSocketHandler(std::string ip, int unsigned port);
	~CClientSocketHandler();

	void stop();
	void init();
	void output();

private:
	std::string m_ip;
	int unsigned m_port;

	void write(std::string message);
	std::vector<std::string> getInfo();
	void printInfo();
	void accept();
	void read();
	void connect();

	std::vector<char> vBuffer;
	std::vector <std::string> readBuffer;
	asio::io_context m_context;
	asio::ip::tcp::socket m_socket;
	std::thread m_thrContext;

	
};
