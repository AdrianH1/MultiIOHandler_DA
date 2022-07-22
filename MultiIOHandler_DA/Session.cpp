#include "Session.h"

using asio::ip::tcp;

void Session::start()
{
    read();
}

void Session::read()
{
    auto self(shared_from_this());
    socket.async_read_some(asio::buffer(data, max_length),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                //do_write(length);
                std::cout << "Bytes available: " << length << std::endl;
                std::cout << "Message is: ";
                std::cout.write(data, length);
                std::cout << std::endl;
                read();
            }
        });
}

void Session::write(std::size_t length)
{
    auto self(shared_from_this());
    asio::async_write(socket, asio::buffer(data, length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                write(512);
            }
        });
}