#include "CMulticastHandler.h"

static const std::string sType = "multicast";

CMulticastHandler::CMulticastHandler(std::string ip, int unsigned port, std::string multicastIP)
	:m_ip(ip), m_port(port), m_multicast(multicastIP), m_socket(m_context), vBuffer(vBufferSize), m_resolver(m_context),
	m_endpoint(asio::ip::udp::v4(), m_port), m_multicastEndpoint(asio::ip::udp::v4(), m_port)
{
	setId(++m_idCounter);
	setModuleType(multicast);
	setConnectedState(false);
	std::cout << "Create Socket Module: " << std::endl;
	printInfo();
}

CMulticastHandler::~CMulticastHandler()
{
	stop();
}

void CMulticastHandler::init()
{
	//Make sure ASIO io_context is running
	if (m_context.stopped())
	{
		m_context.restart();
	}

	//Give the ASIO io_context fake work to keep it running
	asio::io_context::work idleWork(m_context);

	//Run ASIO io_context in separate thread so that reading can be done parallel to main thread
	m_thrContext = std::thread([this]() {m_context.run(); });

	asio::error_code ec;
	m_endpoint = *m_resolver.resolve(m_ip, std::to_string(m_port), ec);
	m_multicastEndpoint = *m_resolver.resolve(m_multicast, std::to_string(m_port), ec);

	m_socket.open(m_endpoint.protocol(), ec);
	m_socket.set_option(asio::ip::udp::socket::reuse_address(true), ec);
	m_socket.bind(m_endpoint, ec);

	m_socket.set_option(asio::ip::multicast::join_group(m_multicastEndpoint.address().to_v4(), m_endpoint.address().to_v4()), ec);

	if (!ec)
	{
		setConnectedState(true);
		std::cout << "Connected!" << std::endl;
		read();
	}
	else
	{
		std::cout << "Failed to connect!" << std::endl;
		m_context.stop();
		if (m_thrContext.joinable()) m_thrContext.join();
	}
}

void CMulticastHandler::read()
{

	asio::ip::udp::endpoint senderEndpoint;
	//Async read function from ASIO
	m_socket.async_receive_from(asio::buffer(vBuffer.data(), vBuffer.size()), senderEndpoint,
		[&](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				readBuffer.push_back(vBuffer);
				//Call write method of all listener in listener table with read data
				if (getWriteToListener())
				{
					for (IIOModule* m : listenerTable)
					{
						m->write(vBuffer);
					}
				}
				//This is no endless recursion because async_read_some is only running if data is recieved
				read();
			}
		}
	);
}

void CMulticastHandler::write(std::vector<char> message)
{
	//lock_guard to prevent simultaneous writing. Lock is released when block ends.
	const std::lock_guard<std::mutex> lock(writeMutex);
	asio::error_code ec;
	if (filterIsSet())
	{
		std::vector<char> filteredMessage = getFilter()->filterData(message);
		m_socket.send_to(asio::buffer(message.data(), message.size()), m_multicastEndpoint);
	}
	else
	{
		m_socket.send_to(asio::buffer(message.data(), message.size()), m_multicastEndpoint);
	}
}

void CMulticastHandler::stop()
{
	setWriteToListener(false);
	setConnectedState(false);
	listenerTable.clear();
	removeFilter();
	m_socket.close();
	m_context.stop();
	if (m_thrContext.joinable()) m_thrContext.join();
}

void CMulticastHandler::connect()
{
	setWriteToListener(true);
}

void CMulticastHandler::output()
{
	for (std::vector<char> v : readBuffer)
	{
		for (char c : v)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	setWriteToListener(true);
}

std::vector<std::vector<std::string>> CMulticastHandler::getInfo()
{
	std::vector<std::vector<std::string>> info;
	std::vector<std::string> parameter;

	parameter.push_back("Type");
	//Use string instead of enum, otherwise there is an int for type in json export
	parameter.push_back(sType);
	info.push_back(parameter);
	parameter.clear();

	parameter.push_back("IP");
	parameter.push_back(m_ip);
	info.push_back(parameter);
	parameter.clear();

	parameter.push_back("Port");
	parameter.push_back(std::to_string(m_port));
	info.push_back(parameter);
	parameter.clear();

	parameter.push_back("Multicast");
	parameter.push_back(m_multicast);
	info.push_back(parameter);
	parameter.clear();

	return info;
}

void CMulticastHandler::printInfo()
{
	std::cout << "ID: " << getId() << " | Type: " << sType << " | IP: " << m_ip << " | Port: " << m_port << " | Multicast: " << m_multicast << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;

}
