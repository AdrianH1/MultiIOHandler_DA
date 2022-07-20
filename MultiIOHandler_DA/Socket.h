#pragma once

#include "stdafx.h"
#include "IOModule.h"
#include "Server.h"

class Socket : public IOModule
{
public:
	Socket() = default;
	Socket(asio::io_context& io_context, std::string ip, int unsigned port);
	~Socket();
	int m_id;

private:
	std::string m_IP;
	int unsigned m_Port;
	void init(std::string ip, int unsigned port);
	void send();
	void recv();
	void printInfo();
	void do_accept();

	asio::ip::tcp::acceptor acceptor_;
	asio::ip::tcp::socket socket_;
};
