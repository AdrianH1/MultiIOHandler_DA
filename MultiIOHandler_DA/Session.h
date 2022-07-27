#pragma once
#include "stdafx.h"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket m_socket, std::vector<std::string> readBuffer)
        : m_socket(std::move(m_socket)), readBuffer(std::move(readBuffer))
    {}

    void start();
    void read();
    void write(std::size_t length);

private:

    tcp::socket m_socket;
    std::vector<std::string> readBuffer;
    enum { max_length = 1024 };
    char data[max_length];
};