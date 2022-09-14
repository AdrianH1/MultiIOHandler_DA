#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CServerSocketHandler : public IIOModule
{
public:
	CServerSocketHandler() = default;
	CServerSocketHandler(std::string ip, int unsigned port);
	~CServerSocketHandler();

	void init();
	void stop();
	void output();


private:
	void write(std::string message);
	void read();
	void connect();
	std::vector<std::string> getInfo();
	void printInfo();

	std::string m_ip;
	int unsigned m_port;

	bool writeToListener = false;

	std::vector<char> vBuffer;
	std::vector <std::string> readBuffer;
	asio::io_context m_context;
	asio::ip::tcp::socket m_socket;
	asio::ip::tcp::acceptor m_acceptor;
	std::thread m_thrContext;
};