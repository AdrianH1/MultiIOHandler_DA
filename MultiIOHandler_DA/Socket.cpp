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
    //asio::error_code for error output

    // Create a context - essentially the platform specific interface
    // asio::io_context
    
    //asio tcp endpoint
    //IP and port

    //asio tcp socket

    //socket.connect

    //check error code to check status

    //if socket.is_open()
    // Check if bytes are available to read with socket.available()
    
    //std::vector<char> vBuffer(bytes)
    //socket.read_some(asio::buffer)

    //TIMING async needed (async_read_some)
    //Context in own thread
    //javidx simple example  https://github.com/OneLoneCoder/olcPixelGameEngine/tree/master/Videos/Networking/Parts1%262

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
