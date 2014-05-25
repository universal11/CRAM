//
//  main.cpp
//  CRAM
//
//  Created by Marc Martinez on 5/11/14.
//  Copyright (c) 2014 the universal framework. All rights reserved.
//

#include "CRAMSession.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>

boost::asio::io_service _ioService;
//boost::asio::ip::tcp::resolver _resolver(_ioService);
//boost::asio::ip::tcp::socket _socket(_ioService);
//boost::array<char, 8192> buffer;
std::string queuePath = "";
std::string receivingServerHostname = "mx1.hotmail.com";
std::string clientAddress = "";
boost::program_options::options_description description("CRAM Utility");

/*
void readHandler(const boost::system::error_code &error, std::size_t bytes_transferred){
    if (!error){
        std::cout << "Read Begin" << std::endl;
        std::cout << std::string(buffer.data(), bytes_transferred) << std::endl;
        std::cout << "Read End" << std::endl;
        _socket.async_read_some(boost::asio::buffer(buffer), readHandler);
    }
    else{
        std::cout << "Could not read!" << std::endl;
    }
}

void writeHandler(const boost::system::error_code &error, std::size_t bytes_transferred){
     boost::asio::async_read(_socket, boost::asio::buffer(buffer), readHandler);
}
 */


void loadSession(std::string sessionPath){
    std::string session = "";
    std::cout << "Loading Session: " << sessionPath << std::endl;
    if(boost::filesystem::exists(sessionPath)){
        boost::filesystem::ifstream fileStream(sessionPath);
        while(fileStream){
            std::string fileLine = "";
            std::getline(fileStream, fileLine);
            session += fileLine + "\r";
            //std::cout << "Session Line: " << fileLine << std::endl;
        }
        
        //CRAMSession cramSession(_ioService, receivingServerHostname, session, clientAddress);
        
        //boost::asio::write(_socket, boost::asio::buffer("HELO miowenfoinwf.com\r\nMAIL FROM: ioenwfoiwenf.com\r\nRCPT TO:darks1de11@hotmail.com\r\nDATA\r\n"));
        //boost::asio::write(_socket, boost::asio::buffer("from:ytftyfftyf@ytcuuyfv.com\nto:darks1de11@hotmail.com\nsubject: oiwefwnefiewnfion\njust a test\r\n.\r\n"));
        
    }
}

void loadQueue(std::string queuePath){
    std::string queueData = "";
    std::cout << "Loading Queue: " << queuePath << std::endl;
    if(boost::filesystem::exists(queuePath) && boost::filesystem::is_directory(queuePath)){
        boost::filesystem::directory_iterator queuePathIterator(queuePath);
        boost::filesystem::directory_iterator endQueuePathIterator;
        
        while(queuePathIterator != endQueuePathIterator){
            std::string sessionPath = queuePath + "/" + queuePathIterator->path().filename().string();
            loadSession(sessionPath);
            queuePathIterator++;
        }

    }
}

void sendQueue(){
    
}

/*
void connectHandler(const boost::system::error_code &error){
    if(!error){
        std::cout << "Connected!" << std::endl;
        loadQueue(queuePath);
        //boost::asio::write(_socket, boost::asio::buffer("\r\n.\r\n"));
       
        _socket.async_read_some(boost::asio::buffer(buffer), readHandler);
    }
    else{
        std::cout << "Could not connect!" << std::endl;
    }
}

void resolveHandler(const boost::system::error_code &error, boost::asio::ip::tcp::resolver::iterator iterator){
    if (!error){
        _socket.async_connect(*iterator, connectHandler);
    }
    else{
        std::cout << "Could not resolve!" << std::endl;
    }
}
*/

int main(int argc, const char * argv[]){
    //std::string receivingServer = "mx1.hotmail.com";
    std::cout << "Resolving: " << receivingServerHostname << std::endl;
    description.add_options()
    ("queue,q", boost::program_options::value<std::string>(), "Queue path.")
    ("bind,b", boost::program_options::value<std::string>(), "Client Address")
    ("help,h", "Help");
    
    boost::program_options::variables_map optionMap;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(description).run(), optionMap);
    boost::program_options::notify(optionMap);
    
    if(optionMap.count("help")){
        std::cout << description << std::endl;
        return 0;
    }
    
    if(optionMap.count("bind")){
        clientAddress = optionMap["bind"].as<std::string>();
    }
    
    if(clientAddress.empty()){ clientAddress = "0.0.0.0"; }
    std::cout << "Bound to: " << clientAddress << std::endl;
    
    if(optionMap.count("queue")){
        queuePath = optionMap["queue"].as<std::string>();
        loadQueue(queuePath);
        CRAMSession cramSession(_ioService, receivingServerHostname, "helo fefeferg.com\r\n", clientAddress);
        CRAMSession cramSession2(_ioService, receivingServerHostname, "helo fefeferg2.com\r\n", clientAddress);
        //boost::asio::ip::tcp::resolver::query query(receivingServer, "smtp");
        //_resolver.async_resolve(query, resolveHandler);
        _ioService.run();
        
    }
    
    
    
    
    // insert code here...
    //std::cout << "Hello, World!\n";
    //_socket.open(boost::asio::ip::tcp::v4());
    //_socket.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(clientAddress), 0));
    //_socket.async_connect(*endpointIterator++, boost::bind(&TCPClient::handleConnect, this, boost::asio::placeholders::error));
    return 0;
}

