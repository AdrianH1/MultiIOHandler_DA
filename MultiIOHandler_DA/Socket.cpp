#include "Socket.h"


Socket::Socket(std::string ip, int unsigned port)
    : m_IP(ip), m_Port(port)
{
    m_id = ++m_idCounter;
    init(ip, port);
}

Socket::~Socket()
{
}

void Socket::init (std::string ip, int unsigned port)
{
    asio::io_context io_context;

    Server s(io_context, ip, port);

    io_context.run();

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
