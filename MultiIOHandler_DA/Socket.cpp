#include "Socket.h"
#include "Session.h"


//Socket::Socket(std::string ip, int unsigned port)
//    : m_IP(ip), m_Port(port)
//{
//    m_id = ++m_idCounter;
//    init(ip, port);
//}

Socket::Socket(asio::io_context& io_context, std::string ip, int unsigned port)
    : m_IP(ip), m_Port(port), acceptor_(io_context, tcp::endpoint(asio::ip::make_address(ip), port)),
    socket_(io_context)
{
    std::cout << "Server started, waiting for connection. Listen on " << ip << ":" << port << std::endl;
    do_accept();
}

Socket::~Socket()
{
}

void Socket::do_accept()
{
    acceptor_.async_accept(socket_,
        [this](std::error_code ec)
        {
            if (!ec)
            {
                std::cout << "client connected" << std::endl;
                std::make_shared<Session>(std::move(socket_))->start();
            }

            do_accept();
        });
}

void Socket::send()
{

}

void Socket::recv()
{

}

void Socket::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_IP << " | Port: " << m_Port << std::endl;
}
