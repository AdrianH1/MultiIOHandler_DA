#pragma once

#include "stdafx.h"
#include "IIOModule.h"
#include "Server.h"

class CSocketHandler : public IIOModule
{
public:
	CSocketHandler() = default;
	CSocketHandler(asio::io_context& io_context, std::string ip, int unsigned port);
	~CSocketHandler();
	int m_id;
	std::vector<std::string> readBuffer;
	void run();

private:
	std::string m_IP;
	int unsigned m_Port;
	void init(std::string ip, int unsigned port);
	void read();
	void write();
	void printInfo();
	void accept();

	asio::io_context &m_ioContext;
	asio::ip::tcp::acceptor m_acceptor;
	asio::ip::tcp::socket m_socket;

	enum { max_length = 1024 };
	char data[max_length];
};
