#include "stdafx.h"
#include "cSerialHandler.h"


CSerialHandler::CSerialHandler(asio::io_service& io_service, std::string port, int bauderate)
    : m_Port(port), m_Baudrate(bauderate), serial(io_service)
{
    //m_id = ++m_idCounter;
    //serial.open(port);
    //serial.set_option(asio::serial_port_base::baud_rate(bauderate));
    //read();

}

void CSerialHandler::run()
{

}

void CSerialHandler::stop()
{

}

void CSerialHandler::handler(
    const asio::error_code& error, // Result of operation.
    std::size_t bytes_transferred // Number of bytes read.
) {};

void CSerialHandler::handle_receive(const asio::error_code& error,
    std::size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Recieved:" << data << std::endl;
    }
}

void CSerialHandler::output()
{
}

void CSerialHandler::read()
{
    serial.async_read_some(asio::buffer(data, max_length),
        [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "Bytes available: " << length << std::endl;
                std::cout << "Message is: ";
                std::cout.write(data, length) << std::endl;
                read();
            }
        });

    //char receive[max_length];
    //serial.async_read_some(asio::buffer(receive, 512), &CSerialHandler::handler);
    //serial.async_read_some(asio::buffer(data, max_length),
    //    std::bind(&CSerialHandler::handle_receive,
    //        this, std::placeholders::_1,
    //        std::placeholders::_2));
    //std::cout << "Message is: ";
    //std::cout.write(data, max_length);
    //std::cout << std::endl;
}

void CSerialHandler::connect()
{
}

void CSerialHandler::write(std::string message)
{
    std::cout << "Enter message: ";
    //char request[max_length];
    std::cin.getline(data, max_length);
    size_t request_length = std::strlen(data);
    serial.async_write_some(asio::buffer(data, max_length),
        std::bind(&CSerialHandler::handle_receive,
            this, std::placeholders::_1,
            std::placeholders::_2));
}

CSerialHandler::~CSerialHandler()
{
}

void CSerialHandler::init()
{

}


int CSerialHandler::getId()
{
    return 0;
}

void CSerialHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | Port: " << m_Port << " | Spped: " << m_Baudrate << std::endl;
}