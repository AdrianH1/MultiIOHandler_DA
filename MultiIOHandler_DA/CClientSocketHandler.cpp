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
    setWriteToListener(true);
}

void CClientSocketHandler::read()
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
                std::string message = "";
                for (int i = 0; i < length; i++)
                {
                    message += vBuffer[i];
                }
                readBuffer.push_back(message);
                //Call write method of all listener in listener table with read data
                if (getWriteToListener())
                {
                    for (IIOModule* m : listenerTable)
                    {
                        m->write(message);
                    }
                }
                //This is no endless recursion because async_read_some is only running if data is recieved
                read();
            }
        }
    );
}

void CClientSocketHandler::write(std::string message)
{
    //lock_guard to prevent simultaneous writing. Lock is released when block ends.
    const std::lock_guard<std::mutex> lock(writeMutex);
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
        setWriteToListener(true);
    }
}

void CClientSocketHandler::stop()
{
    setWriteToListener(false);
    setConnectedState(false);
    listenerTable.clear();
    m_socket.close();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CClientSocketHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << "clientSocket" << " | IP: " << m_ip << " | Port: " << m_port << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}
