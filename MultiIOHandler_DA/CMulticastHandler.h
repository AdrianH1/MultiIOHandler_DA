#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CMulticastHandler : public IIOModule
{
public:
	CMulticastHandler() = default;

	CMulticastHandler(std::string ip, int unsigned port, std::string multicastIP);
	~CMulticastHandler() override;

	void init() override;
	void stop() override;
	void output() override;

private:
	std::string m_ip;
	int unsigned m_port;
	std::string m_multicast;


	void read() override;
	void write(std::vector<char> message) override;
	void connect() override;
	std::vector<std::vector<std::string>> getInfo() override;
	void printInfo() override;

	std::vector<char> vBuffer;
	std::vector<std::vector<char>> readBuffer;
	asio::io_context m_context;
	asio::ip::udp::endpoint m_endpoint;
	asio::ip::udp::endpoint m_senderEndpoint;
	asio::ip::udp::socket m_socket;
	std::thread m_thrContext;
};