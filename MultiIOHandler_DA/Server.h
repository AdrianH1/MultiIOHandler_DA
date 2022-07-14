#pragma once
#include "stdafx.h"

using asio::ip::tcp;

class Server
{
public:
    Server(asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(asio::ip::make_address("192.168.193.100"), port)),
        socket_(io_context)
    {
        std::cout << "Server started, waiting for connection";
        do_accept();
    }

private:
    void do_accept();

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};