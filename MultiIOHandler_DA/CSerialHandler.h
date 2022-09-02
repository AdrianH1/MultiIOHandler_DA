#pragma once
#include "IIOModule.h"
#include <string>

class CSerialHandler  : public IIOModule
{
public:
	CSerialHandler() = default;
	CSerialHandler(std::string port, int bauderate);
	~CSerialHandler();

	void init();
	void stop();

private:
	std::string m_port;
	int m_baudrate;

	void write(std::string message);
	void read();
	void connect();
	void output();
	std::vector<std::string> getInfo();
	void printInfo();

	bool writeToListener = false;

	std::vector<char> vBuffer;
	std::vector <std::string> readBuffer;
	asio::io_context m_context;
	asio::serial_port m_serial;
	std::thread m_thrContext;
};