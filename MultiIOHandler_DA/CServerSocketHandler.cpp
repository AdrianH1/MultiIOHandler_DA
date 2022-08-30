#include "CServerSocketHandler.h"

CServerSocketHandler::CServerSocketHandler(std::string ip, int unsigned port)
	: m_ip(ip), m_port(port), m_socket(m_context), p_socket(new asio::ip::tcp::socket(m_context)),
	m_acceptor(m_context, asio::ip::tcp::endpoint(asio::ip::make_address(ip), port))
{
	m_id = ++m_idCounter;
	m_type = serverSocket;
	std::cout << "Created Server Socket Module: " << std::endl;
	printInfo();
}

CServerSocketHandler::~CServerSocketHandler()
{
	stop();
}

void CServerSocketHandler::init()
{
	//if (m_context.stopped())
	//{
	//	m_context.restart();
	//}

	asio::io_context::work idleWork(m_context);

	m_thrContext = std::thread([this]() {m_context.run(); });

	accept();

}

void CServerSocketHandler::accept()
{
	std::cout << "Server socket started, waiting for connection. Listen on " << m_ip << ":" << m_port << std::endl;
	m_acceptor.async_accept(m_socket,
		[this](std::error_code ec)
		{
			if (!ec)
			{
				std::cout << "client connected: " << m_socket.remote_endpoint() << std::endl;
				std::cout << std::endl << ">>>";
				read();
			}

			//accept();
		});
}

void CServerSocketHandler::stop()
{
	m_context.stop();

	if (m_thrContext.joinable()) m_thrContext.join();

	std::cout << "Server stopped" << std::endl;
}

void CServerSocketHandler::write(std::string message)
{
}

void CServerSocketHandler::read()
{
	m_socket.async_read_some(asio::buffer(data, max_length),
		[&](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				std::cout << "Bytes available: " << length << std::endl;
				std::cout << "Message is: ";
				std::cout.write(data, length) << std::endl;

				readBuffer.push_back(data);

				//std::string message = "";
				//for (int i = 0; i < length; i++)
				//{
				//    message = message + data[i];
				//}
				//readBuffer.push_back(message);
				//std::cout << "buffer: ";
				//for (std::string s : readBuffer)
				//{
				//    std::cout << s;
				//}
				//std::cout << std::endl;

				//write();
				read();
			}
		});
}

void CServerSocketHandler::connect()
{
}

void CServerSocketHandler::output()
{
}

std::vector<std::string> CServerSocketHandler::getInfo()
{
	return std::vector<std::string>();
}

void CServerSocketHandler::printInfo()
{
	std::cout << "ID: " << m_id << " | IP: " << m_ip << " | Port: " << m_port << std::endl;
}
