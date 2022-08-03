#pragma once
#include "IIOModule.h"
#include <string>

class CSerialHandler : public IIOModule
{
public:


	CSerialHandler() = default;
	CSerialHandler(asio::io_service& io_service, std::string port, int bauderate);
	~CSerialHandler();

	int m_id;
	std::string m_Port;
	int m_Baudrate;
	asio::serial_port serial;

	void run();
	void stop();

private:

	void init();
	void write();
	void read();
	void handler(const asio::error_code& error, std::size_t bytes_transferred);
	void handle_receive(const asio::error_code& error, std::size_t bytes_transferred);
	void printInfo();


	enum { max_length = 1024 };
	char data[max_length];
	char receiveBuffer[max_length];
};