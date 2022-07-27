#include "stdafx.h"
#include "cSerial.h"


CSerial::CSerial(asio::io_service& io_service, std::string port, int bauderate)
    : m_Port(port), m_Baudrate(bauderate), serial(io_service)
{
    m_id = ++m_idCounter;
    serial.open(port);
    serial.set_option(asio::serial_port_base::baud_rate(bauderate));
    read();

}

void CSerial::handler(
    const asio::error_code& error, // Result of operation.
    std::size_t bytes_transferred // Number of bytes read.
) {};

void CSerial::handle_receive(const asio::error_code& error,
    std::size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Recieved:" << data << std::endl;
    }
}

void CSerial::read()
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
    //serial.async_read_some(asio::buffer(receive, 512), &CSerial::handler);
    //serial.async_read_some(asio::buffer(data, max_length),
    //    std::bind(&CSerial::handle_receive,
    //        this, std::placeholders::_1,
    //        std::placeholders::_2));
    //std::cout << "Message is: ";
    //std::cout.write(data, max_length);
    //std::cout << std::endl;
}

void CSerial::write()
{
    std::cout << "Enter message: ";
    //char request[max_length];
    std::cin.getline(data, max_length);
    size_t request_length = std::strlen(data);
    serial.async_write_some(asio::buffer(data, max_length),
        std::bind(&CSerial::handle_receive,
            this, std::placeholders::_1,
            std::placeholders::_2));
}

CSerial::~CSerial()
{
}

void CSerial::init()
{

}

void CSerial::send()
{

}

void CSerial::recv()
{

}

void CSerial::printInfo()
{
    std::cout << "ID: " << m_id << " | Port: " << m_Port << " | Spped: " << m_Baudrate << std::endl;
}