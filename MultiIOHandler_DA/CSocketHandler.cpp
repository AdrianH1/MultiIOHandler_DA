#include "CSocketHandler.h"
#include "Session.h"

CSocketHandler::CSocketHandler(asio::io_context& io_context, std::string ip, int unsigned port)
    : m_IP(ip), m_Port(port), m_ioContext(io_context), m_acceptor(io_context, tcp::endpoint(asio::ip::make_address(ip), port)),
    m_socket(io_context)
{ 
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    //std::thread th1(&CSocketHandler::accept, this);
    //std::thread* th1 = new std::thread(&CSocketHandler::accept, this);
    //th1->join();
    //run();
    accept();
}

CSocketHandler::~CSocketHandler()
{
}

void CSocketHandler::run()
{
    //m_ioContext.run();
    std::cout << "Server started, waiting for connection. Listen on " << m_IP << ":" << m_Port << std::endl;
    accept();
}

void CSocketHandler::accept()
{
    m_acceptor.async_accept(m_socket,
        [this](std::error_code ec)
        {
            if (!ec)
            {
                std::cout << "client connected" << std::endl;
                //read();
                //std::make_shared<Session>(std::move(m_socket), std::move(readBuffer))->read();
            }
            accept();
        });
}


void CSocketHandler::read()
{
    //m_socket.async_read_some(asio::buffer(data, max_length),
    //    [this](std::error_code ec, std::size_t length)
    //    {
    //        if (!ec)
    //        {
    //            std::cout << "Bytes available: " << length << std::endl;
    //            std::cout << "Message is: ";
    //            std::cout.write(data, length) << std::endl;

    //            //std::string message = "";
    //            //for (int i = 0; i < length; i++)
    //            //{
    //            //    message = message + data[i];
    //            //}
    //            //readBuffer.push_back(message);
    //            //std::cout << "buffer: ";
    //            //for (std::string s : readBuffer)
    //            //{
    //            //    std::cout << s;
    //            //}
    //            //std::cout << std::endl;
    //            
    //            //write();
    //            read();
    //        }
    //    });
}

void CSocketHandler::write()
{

}

void CSocketHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_IP << " | Port: " << m_Port << std::endl;
}
