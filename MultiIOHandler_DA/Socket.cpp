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
    asio::error_code ec;
    asio::io_context context;
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 443);
    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec)
    {
        std::cout << "Connected" << std::endl;
    }
    else
    {
        std::cout << "Failed to connected" << std::endl;

    }



    /*
    asio::error_code ec;

    // Create a context - essentially the platform specific interface
    asio::io_context io_context;
    
    //asio tcp socket
    asio::ip::tcp::socket socket(io_context);
    asio::ip::tcp::resolver resolver(io_context);

    //socket.connect
    asio::connect(socket, resolver.resolve("127.0.0.1", "123123"));


    std::cout << "Enter message: ";
    char request[1024];
    std::cin.getline(request, 1024);
    size_t request_length = std::strlen(request);
    asio::write(socket, asio::buffer(request, request_length));
    */

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
