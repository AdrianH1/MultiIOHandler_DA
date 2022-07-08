#include "stdafx.h"
#include "Socket.h"


Socket::Socket(std::string ip, int port)
    : m_IP(ip), m_Port(port)
{
    m_id = ++m_idCounter;
}

Socket::~Socket()
{
}

void Socket::init()
{

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
