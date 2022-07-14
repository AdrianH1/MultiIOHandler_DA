#include "Session.h"

using asio::ip::tcp;

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(data_, max_length),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write(length);
                std::cout << "Reply is: ";
                std::cout.write(data_, max_length);
                std::cout << std::endl;
            }
        });
}

void Session::do_write(std::size_t length)
{
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                do_read();
            }
        });
}