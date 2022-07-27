#include "CSocketHandler.h"
#include "Session.h"

CSocketHandler::CSocketHandler(asio::io_context& io_context, std::string ip, int unsigned port)
    : m_IP(ip), m_Port(port), acceptor(io_context, tcp::endpoint(asio::ip::make_address(ip), port)),
    socket(io_context)
{
    std::cout << "Server started, waiting for connection. Listen on " << ip << ":" << port << std::endl;
    accept();
}

CSocketHandler::CSocketHandler(asio::io_context& io_context)
    : acceptor(io_context, tcp::endpoint(asio::ip::make_address("192.168.193.100"), 64000)),
    socket(io_context)
{
    std::cout << "Server started, waiting for connection. Listen on " << "192.168.193.100" << ":" << "64000" << std::endl;
    accept_write();
}

CSocketHandler::~CSocketHandler()
{
}

void CSocketHandler::accept()
{
    acceptor.async_accept(socket,
        [this](std::error_code ec)
        {
            if (!ec)
            {
                std::cout << "client connected" << std::endl;
                std::make_shared<Session>(std::move(socket), std::move(readBuffer))->read();
            }

            accept();
        });
}

void CSocketHandler::accept_write()
{
    acceptor.async_accept(socket,
        [this](std::error_code ec)
        {
            if (!ec)
            {
                std::cout << "client connected" << std::endl;
                std::make_shared<Session>(std::move(socket), std::move(readBuffer))->write(512);
            }

            accept();
        });
}

void CSocketHandler::write()
{

}

void CSocketHandler::send()
{

}

void CSocketHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_IP << " | Port: " << m_Port << std::endl;
}
