#pragma once
#include "IOModule.h"
#include <string>

class Serial : public IOModule
{
public:


	Serial() = default;
	Serial(asio::io_service& io_service, std::string port, int bauderate);
	~Serial();

	int m_id;
	std::string m_Port;
	int m_Baudrate;
	asio::serial_port serial;

private:
	void init();
	void send();
	void recv();
	void read();
	void write();
	void handler(const asio::error_code& error, std::size_t bytes_transferred);
	void handle_receive(const asio::error_code& error, std::size_t bytes_transferred);
	void printInfo();


	enum { max_length = 1024 };
	char data[max_length];
	char receiveBuffer[max_length];
};