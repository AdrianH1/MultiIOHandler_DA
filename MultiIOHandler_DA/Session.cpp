#include "Session.h"

using asio::ip::tcp;

void Session::start()
{
    read();
}

void Session::read()
{
    auto self(shared_from_this());
    m_socket.async_read_some(asio::buffer(data, max_length),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "Bytes available: " << length << std::endl;
                std::cout << "Message is: ";
                std::cout.write(data, length) << std::endl;
                std::string message = "";
                for (int i = 0; i < length; i++)
                {
                    message = message + data[i];
                }
                readBuffer.push_back(message);
                std::cout << "buffer: ";
                for (std::string s : readBuffer)
                {
                    std::cout << s;
                }
                std::cout << std::endl;
                write(length);
                //read();
            }
        });
}

void Session::write(std::size_t length)
{
    auto self(shared_from_this());
    asio::async_write(m_socket, asio::buffer(data, length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                read();
            }
        });
}