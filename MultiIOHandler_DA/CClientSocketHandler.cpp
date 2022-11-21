#include "CClientSocketHandler.h"

static const std::string sType = "clientsocket";

CClientSocketHandler::CClientSocketHandler(std::string ip, int unsigned port)
    : m_ip(ip), m_port(port), m_socket(m_context), m_resolver(m_context), vBuffer(vBufferSize)
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
    asio::ip::tcp::endpoint endpoint = *m_resolver.resolve(m_ip, std::to_string(m_port), ec);

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

void CClientSocketHandler::write(std::vector<char> message)
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

std::vector<std::vector<std::string>> CClientSocketHandler::getInfo()
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

void CClientSocketHandler::connect()
{
    setWriteToListener(true);
}

void CClientSocketHandler::stop()
{
    setWriteToListener(false);
    setConnectedState(false);
    listenerTable.clear();
    removeFilter();
    m_socket.close();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CClientSocketHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << sType << " | IP: " << m_ip << " | Port: " << m_port << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}
