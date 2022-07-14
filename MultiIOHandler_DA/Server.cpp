#include "Server.h"
#include "Session.h"

using asio::ip::tcp;

void Server::do_accept()
{
    acceptor_.async_accept(socket_,
        [this](std::error_code ec)
        {
            if (!ec)
            {
                std::cout << "client connected";
                std::make_shared<Session>(std::move(socket_))->start();
            }

            do_accept();
        });
}