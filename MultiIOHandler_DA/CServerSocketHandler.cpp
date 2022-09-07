#include "CServerSocketHandler.h"

CServerSocketHandler::CServerSocketHandler(int unsigned port)
	: m_port(port), m_socket(m_context), vBuffer(vBufferSize),
	m_acceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
	m_id = ++m_idCounter;
	m_type = serverSocket;
    m_connected = false;
	std::cout << "Created Server Socket Module: " << std::endl;
	printInfo();
}

CServerSocketHandler::~CServerSocketHandler()
{
	stop();
}

void CServerSocketHandler::init()
{
	if (m_context.stopped())
	{
		m_context.restart();
	}

	asio::io_context::work idleWork(m_context);

	m_thrContext = std::thread([this]() {m_context.run(); });
    
	std::cout << "Server socket started, waiting for connection" << std::endl;
	m_acceptor.async_accept(m_socket,
		[this](std::error_code ec)
		{
			if (!ec)
			{
				std::cout << "client connected: " << m_socket.remote_endpoint() << std::endl;
				std::cout << std::endl << ">>>";
                m_connected = true;
				read();
			}
		});

}

void CServerSocketHandler::stop()
{
    writeToListener = false;
    m_connected = false;
    listenerTable.clear();

	m_context.stop();

	if (m_thrContext.joinable()) m_thrContext.join();
}

void CServerSocketHandler::write(std::string message)
{
    asio::error_code ec;
    m_socket.write_some(asio::buffer(message.data(), message.size()), ec);
}

void CServerSocketHandler::read()
{
    if (readBuffer.size() == bufferMax)
    {
        readBuffer.erase(readBuffer.begin());
    }

    m_socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::string message = "";
                for (int i = 0; i < length; i++)
                {
                    message += vBuffer[i];
                }
                readBuffer.push_back(message);
                if (writeToListener)
                {
                    for (IIOModule* m : listenerTable)
                    {
                        m->write(message);
                    }
                }
                read();
            }
        }
    );
}

void CServerSocketHandler::connect()
{
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
}

void CServerSocketHandler::output()
{
    for (std::string s : readBuffer)
    {
        std::cout << s << std::endl;
    }
    writeToListener = true;
}

std::vector<std::string> CServerSocketHandler::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(m_id));
    info.push_back(std::to_string(m_type));
    info.push_back(std::to_string(m_port));
    return info;
}

void CServerSocketHandler::printInfo()
{
	std::cout << "ID: " << m_id << " | Type: " << "serverSocket" << " | Port: " << m_port << " | Connected: " << (m_connected ? "true" : "false") << std::endl;
}
