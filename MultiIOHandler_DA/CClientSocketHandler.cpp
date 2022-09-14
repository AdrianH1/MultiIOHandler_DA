#include "CClientSocketHandler.h"

CClientSocketHandler::CClientSocketHandler(std::string ip, int unsigned port)
    : m_ip(ip), m_port(port), m_socket(m_context), vBuffer(vBufferSize)
{
    setId(++m_idCounter);
    setModuleType(clientSocket);
    setConnectedState(false);
    std::cout << "Created Socket Module: " << std::endl;
    printInfo();
}

CClientSocketHandler::~CClientSocketHandler()
{
    stop();
}

void CClientSocketHandler::init()
{
    if (m_context.stopped())
    {
        m_context.restart();
    }

    asio::io_context::work idleWork(m_context);

    m_thrContext = std::thread([this]() {m_context.run(); });

    asio::error_code ec;
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(m_ip, ec), m_port);

    m_socket.connect(endpoint, ec);

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

void CClientSocketHandler::output()
{
    for (std::string s : readBuffer)
    {
        std::cout << s << std::endl;
    }
    writeToListener = true;
}

void CClientSocketHandler::read()
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

void CClientSocketHandler::write(std::string message)
{
    asio::error_code ec;
    if (filterIsSet())
    {
        std::string filteredMessage = getFilter()->filterData(message);
        m_socket.write_some(asio::buffer(filteredMessage.data(), filteredMessage.size()), ec);
    }
    else
    {
        m_socket.write_some(asio::buffer(message.data(), message.size()), ec);
    }
}

std::vector<std::string> CClientSocketHandler::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(getId()));
    info.push_back(std::to_string(getModuleType()));
    info.push_back(m_ip);
    info.push_back(std::to_string(m_port));
    return info;
}

void CClientSocketHandler::connect()
{
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
}

void CClientSocketHandler::stop()
{
    writeToListener = false;
    setConnectedState(false);
    listenerTable.clear();
    m_socket.close();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CClientSocketHandler::accept()
{
    
}

void CClientSocketHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << "clientSocket" << " | IP: " << m_ip << " | Port: " << m_port << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}
