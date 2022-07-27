#include "CSocketHandler.h"
#include "Session.h"

CSocketHandler::CSocketHandler(asio::io_context& io_context, std::string ip, int unsigned port)
    : m_IP(ip), m_Port(port), 
      m_acceptor(m_ioContext,tcp::endpoint(asio::ip::make_address(ip), port)),
      m_socket(m_ioContext)
{ 
    m_ioContext.run();
    //accept();
}

CSocketHandler::~CSocketHandler()
{
}

void CSocketHandler::accept()
{
    std::cout << "Server started, waiting for connection. Listen on " << m_IP << ":" << m_Port << std::endl;
    m_acceptor.async_accept(m_socket,
        [this](std::error_code ec)
        {
            if (!ec)
            {
                std::cout << "client connected" << std::endl;
                read();
                //std::make_shared<Session>(std::move(m_socket), std::move(readBuffer))->read();
            }

            accept();
        });
}


void CSocketHandler::read()
{
    m_socket.async_read_some(asio::buffer(data, max_length),
        [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "Bytes available: " << length << std::endl;
                std::cout << "Message is: ";
                std::cout.write(data, length) << std::endl;

                //std::string message = "";
                //for (int i = 0; i < length; i++)
                //{
                //    message = message + data[i];
                //}
                //readBuffer.push_back(message);
                //std::cout << "buffer: ";
                //for (std::string s : readBuffer)
                //{
                //    std::cout << s;
                //}
                //std::cout << std::endl;
                
                //write();
                read();
            }
        });
}

void CSocketHandler::write()
{

}

void CSocketHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_IP << " | Port: " << m_Port << std::endl;
}
