#include "CSocketHandler.h"
#include "Session.h"

size_t bufferMax = 50;


CSocketHandler::CSocketHandler(std::string ip, int unsigned port)
    : m_ip(ip), m_port(port), m_socket(m_context), vBuffer(1*512)
{
    m_id = ++m_idCounter;
    m_type = clientSocket;
    std::cout << "Created Socket Module: " << std::endl;
    printInfo();
}

CSocketHandler::~CSocketHandler()
{
    stop();
}

//void CSocketHandler::run()
//{
//    //asio::io_context::work idleWork(m_context);
//
//    //m_thrContext = std::thread([this]() {m_context.run(); });
//
//    //init();
//}

void CSocketHandler::init()
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

void CSocketHandler::output()
{
    for (std::string s : readBuffer)
    {
        std::cout << s << std::endl;
    }
    outputToConsole = true;
}

void CSocketHandler::read()
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
                //std::cout << "\n\nRead " << length << " bytes\n\n";
                std::string message = "";
                for (int i = 0; i < length; i++)
                {
                    message += vBuffer[i];
                    //std::cout << vBuffer[i];
                }
                readBuffer.push_back(message);
                if (outputToConsole)
                {
                    std::cout << message << std::endl;
                }
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

void CSocketHandler::write(std::string message)
{
    asio::error_code ec;
    m_socket.write_some(asio::buffer(message.data(), message.size()), ec);
}

std::vector<std::string> CSocketHandler::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(m_id));
    info.push_back(std::to_string(m_type));
    info.push_back(m_ip);
    info.push_back(std::to_string(m_port));
    return info;
}

void CSocketHandler::connect()
{
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
}

void CSocketHandler::stop()
{
    writeToListener = false;
    outputToConsole = false;
    m_socket.close();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CSocketHandler::accept()
{
    
}

int CSocketHandler::getId()
{
    return m_id;
}

void CSocketHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_ip << " | Port: " << m_port << std::endl;
}
