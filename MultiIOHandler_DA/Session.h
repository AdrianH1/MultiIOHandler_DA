#pragma once
#include "stdafx.h"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket)
        : socket(std::move(socket))
    {}

    void start();
    void read();
    void write(std::size_t length);

private:

    tcp::socket socket;
    enum { max_length = 1024 };
    char data[max_length];
};