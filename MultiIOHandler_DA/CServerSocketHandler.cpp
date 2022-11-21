#include "CServerSocketHandler.h"

static const std::string sType = "serversocket";

CServerSocketHandler::CServerSocketHandler(std::string ip, int unsigned port)
	: m_ip(ip), m_port(port), m_socket(m_context), vBuffer(vBufferSize),
	m_acceptor(m_context), m_resolver(m_context)
{
    setId(++m_idCounter);
    setModuleType(serverSocket);
    setConnectedState(false);
	std::cout << "Created Server Socket Module: " << std::endl;
	printInfo();
}

CServerSocketHandler::~CServerSocketHandler()
{
	stop();
}

void CServerSocketHandler::init()
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

    //Create ASIO Endpoint with user specific IP, Port
    asio::error_code ec;
    asio::ip::tcp::endpoint endpoint = *m_resolver.resolve(m_ip, std::to_string(m_port), ec);
    m_acceptor.open(endpoint.protocol());
    m_acceptor.bind(endpoint, ec);
    if (!ec)
    {
        std::cout << "Server socket started, waiting for connection" << std::endl;
        //ASIO Acceptor waits for a client to connect and accept the connection
        m_acceptor.listen(2);
        m_acceptor.async_accept(m_socket,
            [this](std::error_code ec)
            {
                if (!ec)
                {
                    std::cout << "client connected: " << m_socket.remote_endpoint() << std::endl;
                    std::cout << std::endl << ">>>";
                    setConnectedState(true);
                    read();
                }
            });
    } 
    else
    {
        std::cout << "Failed to connect because of wrong IP!" << std::endl;
        m_context.stop();
        if (m_thrContext.joinable()) m_thrContext.join();
    }
}

void CServerSocketHandler::stop()
{
    setWriteToListener(false);
    setConnectedState(false);
    listenerTable.clear();
    removeFilter();
    m_acceptor.close();
	m_context.stop();
	if (m_thrContext.joinable()) m_thrContext.join();
}

void CServerSocketHandler::write(std::vector<char> message)
{
    //lock_guard to prevent simultaneous writing. Lock is released when block ends.
    const std::lock_guard<std::mutex> lock(writeMutex);
    asio::error_code ec;
    if (filterIsSet())
    {
        std::vector<char> filteredMessage = getFilter()->filterData(message);
        m_socket.write_some(asio::buffer(filteredMessage.data(), filteredMessage.size()), ec);
    }
    else
    {
        m_socket.write_some(asio::buffer(message.data(), message.size()), ec);
    }
}

void CServerSocketHandler::read()
{
    //Keep readBuffer size in check
    if (readBuffer.size() == bufferMax)
    {
        readBuffer.erase(readBuffer.begin());
    }

    //Async read function from ASIO
    m_socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
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

void CServerSocketHandler::connect()
{
    setWriteToListener(true);
}

void CServerSocketHandler::output()
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

std::vector<std::vector<std::string>> CServerSocketHandler::getInfo()
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

    return info;
}

void CServerSocketHandler::printInfo()
{
	std::cout << "ID: " << getId() << " | Type: " << sType << " | IP: " << m_ip << " | Port: " << m_port << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}
