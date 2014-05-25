//
//  CRAMSession.cpp
//  CRAM
//
//  Created by Marc Martinez on 5/24/14.
//  Copyright (c) 2014 the universal framework. All rights reserved.
//

#include "CRAMSession.h"
#include <boost/asio.hpp>
#include<boost/array.hpp>
#include <boost/thread/thread.hpp>


void CRAMSession::handleRead(const boost::system::error_code &error, std::size_t bytes_transferred){
    if(error == boost::asio::error::eof){
        std::cout << "Connection closed!" << std::endl;
        std::cout << "Response: " << this->response << std::endl;
        return;
    }
    if(!error){
        this->response += std::string(this->readBuffer.data(), bytes_transferred);
        //std::cout << "Response: " << response << std::endl;
        
        this->socket.async_receive(boost::asio::buffer(this->readBuffer), boost::bind(&CRAMSession::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}

void CRAMSession::handleConnect(const boost::system::error_code &error){
    if(!error){
        std::cout << "Request: " << this->data << std::endl;
        this->write(this->data);
        this->write("\r\nquit\r\n");
        this->socket.async_receive(boost::asio::buffer(this->readBuffer), boost::bind(&CRAMSession::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        //std::cout << "Response: " << std::string(this->readBuffer.data()) << std::endl;
    }
    else{
        std::cout << error << std::endl;
    }
    
    //boost::asio::async_read(this->socket, boost::asio::buffer(this->readBuffer, 8), boost::bind(&CRAMController::handleRead, this, boost::asio::placeholders::error));
}


CRAMSession::CRAMSession(boost::asio::io_service &_ioService, std::string receivingServerHostname, std::string data, std::string clientAddress) : ioService(_ioService), socket(_ioService){
    std::cout << "Spawning TCP Client" << std::endl;
    boost::asio::ip::tcp::resolver resolver(_ioService);
    boost::asio::ip::tcp::resolver::query query(receivingServerHostname, "smtp");
    boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);
    this->data = data;
    this->clientAddress = clientAddress;
    this->socket.open(boost::asio::ip::tcp::v4());
    //this->socket.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(clientAddress), 0));
    this->socket.async_connect(*endpointIterator++, boost::bind(&CRAMSession::handleConnect, this, boost::asio::placeholders::error));
    
}



void CRAMSession::read(){
    //boost::asio::async_read(this->socket, boost::asio::buffer(this->readBuffer, 8), boost::bind(&CRAMController::handleRead, this, boost::asio::placeholders::error));
    
}



void CRAMSession::close(){
    this->socket.close();
}

void CRAMSession::write(std::string data){
    boost::asio::write(this->socket, boost::asio::buffer(data));
}