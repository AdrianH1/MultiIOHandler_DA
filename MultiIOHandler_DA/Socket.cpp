#include "stdafx.h"
#include "Socket.h"


Socket::Socket(std::string IP, int Port)
    : m_IP(IP), m_Port(Port)
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
