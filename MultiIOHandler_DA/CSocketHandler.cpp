#include "CSocketHandler.h"
#include "Session.h"

CSocketHandler::CSocketHandler(std::string ip, int unsigned port)
    : m_IP(ip), m_Port(port), m_acceptor(m_ioContext, asio::ip::tcp::endpoint(asio::ip::make_address(ip), port))
    //: m_IP(ip), m_Port(port), m_acceptor(m_ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    //std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    //std::thread th1(&CSocketHandler::accept, this);
    //std::thread* th1 = new std::thread(&CSocketHandler::accept, this);
    //th1->join();
    //run();
    //accept();
}

CSocketHandler::~CSocketHandler()
{
    stop();
}

void CSocketHandler::run()
{
    try
    {
        accept();

        m_threadContext = std::thread([this]() {m_ioContext.run(); });
       
    }
    catch (const std::exception&)
    {

    }

    std::cout << "Server started" << std::endl;
}

void CSocketHandler::stop()
{
    m_ioContext.stop();

    if (m_threadContext.joinable()) m_threadContext.join();

    std::cout << "Server stopped" << std::endl;
}

void CSocketHandler::accept()
{
    m_acceptor.async_accept(
        [this](std::error_code ec, asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::cout << "client connected: " << socket.remote_endpoint() << std::endl;
                std::make_shared<Session>(std::move(socket), std::move(readBuffer))->read();
            }
            //accept(); //Only one Client should be able to connect
        });
}


void CSocketHandler::read()
{
    //socket->async_read_some(asio::buffer(data, max_length),
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
