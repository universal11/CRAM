//
//  CRAMSession.h
//  CRAM
//
//  Created by Marc Martinez on 5/24/14.
//  Copyright (c) 2014 the universal framework. All rights reserved.
//

#ifndef __CRAM__CRAMSession__
#define __CRAM__CRAMSession__

#include <iostream>
#include <boost/asio.hpp>
#include<boost/array.hpp>
#include <boost/thread/thread.hpp>

#endif /* defined(__CRAM__CRAMSession__) */

class CRAMSession{
public:
    CRAMSession(boost::asio::io_service &_ioService, std::string receivingServerHostname, std::string data, std::string clientAddress);
    void read();
    void write(std::string data);
    void close();
    
private:
    void handleConnect(const boost::system::error_code &error);
    void handleRead(const boost::system::error_code &error, std::size_t bytes_transferred);
    boost::asio::io_service &ioService;
    boost::asio::ip::tcp::socket socket;
    boost::array<char, 1024> readBuffer;
    std::string response;
    std::string data;
    std::string clientAddress;
    
};