#include "CSocketHandler.h"
#include "Session.h"

CSocketHandler::CSocketHandler(std::string ip, int unsigned port)
    : m_IP(ip), m_port(port), m_socket(m_context), vBuffer(1*1024)
{
    m_id = ++m_idCounter;
    std::cout << "Created Socket: " << std::endl;
    printInfo();
}

CSocketHandler::~CSocketHandler()
{
    stop();
}

void CSocketHandler::init()
{
    try
    {
        asio::error_code ec;

        asio::io_context::work idleWork(m_context);

        m_thrContext = std::thread([this]() {m_context.run(); });

        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(m_IP, ec), m_port);

        m_socket.connect(endpoint, ec);

        if (!ec)
        {
            std::cout << "Connected!" << std::endl;
        }
        else
        {
            std::cout << "Failed to connect!" << std::endl;
        }

        //run();
    }
    catch (const std::exception&)
    {

    }
}

void CSocketHandler::run()
{
    if (m_socket.is_open())
    {
        getData(m_socket);

        //socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

    }
}

void CSocketHandler::getData(asio::ip::tcp::socket& m_socket)
{
    m_socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "\n\nRead " << length << " bytes\n\n";

                for (int i = 0; i < length; i++)
                {
                    std::cout << vBuffer[i];
                }

                getData(m_socket);
            }
        }
    );
}

void CSocketHandler::stop()
{
    m_context.stop();

    if (m_thrContext.joinable()) m_thrContext.join();

    std::cout << "Disconnected!" << std::endl;
}

void CSocketHandler::accept()
{
    
}


void CSocketHandler::read()
{
}

void CSocketHandler::write()
{

}

void CSocketHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_IP << " | Port: " << m_port << std::endl;
}
