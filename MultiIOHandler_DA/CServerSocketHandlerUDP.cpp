#include "CServerSocketHandlerUDP.h"

CServerSocketHandlerUDP::CServerSocketHandlerUDP(std::string ip, int unsigned port)
    : m_ip(ip), m_port(port), m_socket(m_context), vBuffer(vBufferSize),
    m_endpoint(asio::ip::make_address(m_ip), m_port)
{
    setId(++m_idCounter);
    setModuleType(serverSocketUDP);
    setConnectedState(false);
    std::cout << "Created Server Socket Module: " << std::endl;
    printInfo();
}

CServerSocketHandlerUDP::~CServerSocketHandlerUDP()
{
    stop();
}

void CServerSocketHandlerUDP::init()
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
    //asio::ip::udp::endpoint endpoint(asio::ip::make_address(m_ip, ec), m_port);

    m_socket.open(asio::ip::udp::v4());
    m_socket.bind(m_endpoint, ec);

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

void CServerSocketHandlerUDP::stop()
{
    setWriteToListener(false);
    setConnectedState(false);
    listenerTable.clear();
    removeFilter();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CServerSocketHandlerUDP::write(std::vector<char> message)
{
    //lock_guard to prevent simultaneous writing. Lock is released when block ends.
    const std::lock_guard<std::mutex> lock(writeMutex);
    asio::error_code ec;
    if (filterIsSet())
    {
        std::vector<char> filteredMessage = getFilter()->filterData(message);
        m_socket.send(asio::buffer(filteredMessage.data(), filteredMessage.size()));
    }
    else
    {
        m_socket.send(asio::buffer(message.data(), message.size()));
    }
}

void CServerSocketHandlerUDP::read()
{
    //Keep readBuffer size in check
    if (readBuffer.size() == bufferMax)
    {
        readBuffer.erase(readBuffer.begin());
    }

    //Async read function from ASIO
    m_socket.async_receive(asio::buffer(vBuffer.data(), vBuffer.size()),
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

void CServerSocketHandlerUDP::connect()
{
    setWriteToListener(true);
}

void CServerSocketHandlerUDP::output()
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

std::vector<std::string> CServerSocketHandlerUDP::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(getId()));
    info.push_back(std::to_string(getModuleType()));
    info.push_back(m_ip);
    info.push_back(std::to_string(m_port));
    return info;
}

void CServerSocketHandlerUDP::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << "serverSocketUDP" << " | IP: " << m_ip << " | Port: " << m_port << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}
