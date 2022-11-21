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

	//Buffer for ASIO async_read_some function
	std::vector<char> vBuffer;
	//Buffer for storing already read data
	std::vector<std::vector<char>> readBuffer;
	//ASIO context, used to perform ASIO functions
	asio::io_context m_context;
	//ASIO resolver, used to resolve hostnames or IPs
	asio::ip::udp::resolver m_resolver;
	//ASIO endpoint
	asio::ip::udp::endpoint m_endpoint;
	//ASIO endpoint
	asio::ip::udp::endpoint m_multicastEndpoint;
	//ASIO socket, used to read from device
	asio::ip::udp::socket m_socket;
	//Thread to run m_context separatly from main thread
	std::thread m_thrContext;
};