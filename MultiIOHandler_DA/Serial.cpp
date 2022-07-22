#include "stdafx.h"
#include "Serial.h"


Serial::Serial(asio::io_service& io_service, std::string port, int bauderate)
    : m_Port(port), m_Baudrate(bauderate), serial(io_service)
{
    m_id = ++m_idCounter;
    serial.open(port);
    serial.set_option(asio::serial_port_base::baud_rate(bauderate));
    read();

}

void Serial::handler(
    const asio::error_code& error, // Result of operation.
    std::size_t bytes_transferred // Number of bytes read.
) {};

void Serial::handle_receive(const asio::error_code& error,
    std::size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Recieved:" << data << std::endl;
    }
}

void Serial::read()
{

    //char receive[max_length];
    //serial.async_read_some(asio::buffer(receive, 512), &Serial::handler);
    serial.async_read_some(asio::buffer(data, max_length),
        std::bind(&Serial::handle_receive,
            this, std::placeholders::_1,
            std::placeholders::_2));
    std::cout << "Message is: ";
    std::cout.write(data, max_length);
    std::cout << std::endl;
}

void Serial::write()
{
    std::cout << "Enter message: ";
    //char request[max_length];
    std::cin.getline(data, max_length);
    size_t request_length = std::strlen(data);
    serial.async_write_some(asio::buffer(data, max_length),
        std::bind(&Serial::handle_receive,
            this, std::placeholders::_1,
            std::placeholders::_2));
}

Serial::~Serial()
{
}

void Serial::init()
{

}

void Serial::send()
{

}

void Serial::recv()
{

}

void Serial::printInfo()
{
    std::cout << "ID: " << m_id << " | Port: " << m_Port << " | Spped: " << m_Baudrate << std::endl;
}