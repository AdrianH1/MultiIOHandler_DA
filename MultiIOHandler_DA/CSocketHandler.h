#pragma once

#include "stdafx.h"
#include "IIOModule.h"
#include "Server.h"

class CSocketHandler : public IIOModule
{
public:
	CSocketHandler() = default;
	CSocketHandler(asio::io_context& io_context, std::string ip, int unsigned port);
	CSocketHandler(asio::io_context& io_context);
	~CSocketHandler();
	int m_id;
	std::vector<std::string> readBuffer;

private:
	std::string m_IP;
	int unsigned m_Port;
	void init(std::string ip, int unsigned port);
	void write();
	void read();
	void printInfo();
	void accept();
	void accept_write();

	asio::ip::tcp::acceptor acceptor;
	asio::ip::tcp::socket socket;
};
