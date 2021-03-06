#pragma once

#include "stdafx.h"
#include "IOModule.h"
#include "Server.h"

class Socket : public IOModule
{
public:
	Socket() = default;
	Socket(asio::io_context& io_context, std::string ip, int unsigned port);
	Socket(asio::io_context& io_context);
	~Socket();
	int m_id;
	std::vector<std::string> readBuffer;

private:
	std::string m_IP;
	int unsigned m_Port;
	void init(std::string ip, int unsigned port);
	void send();
	void recv();
	void printInfo();
	void accept();
	void accept_write();

	asio::ip::tcp::acceptor acceptor;
	asio::ip::tcp::socket socket;
};
