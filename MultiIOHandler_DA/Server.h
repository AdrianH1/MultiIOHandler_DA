//#pragma once
//#include "stdafx.h"
//
//using asio::ip::tcp;
//
//class Server
//{
//public:
//    Server(asio::io_context& io_context, std::string ip, int unsigned port)
//        : acceptor_(io_context, tcp::endpoint(asio::ip::make_address(ip), port)),
//        socket_(io_context)
//    {
//        std::cout << "Server started, waiting for connection. Listen on " << ip << ":" << port << std::endl;
//        do_accept();
//    }
//
//private:
//    void do_accept();
//
//    tcp::acceptor acceptor_;
//    tcp::socket socket_;
//};