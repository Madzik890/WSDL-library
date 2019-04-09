/*
 * Main class, which cumulates all components to try connect with WSDL's service.
 */

/* 
 * File:   client.hpp
 * Author: madzik
 *
 * Created on March 6, 2019, 2:55 PM
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_pton()
#include <netdb.h> // gethostbyname()

#include "HTTP/HTTP.hpp"
#include "Request.hpp"
#include "Response.hpp"

#define CLIENT_MAXRECV_BUFF 4096

namespace WSDL
{

    class client
    {
    private:
        struct sockaddr_in m_service;
        int m_socket;
       
    public:
        client();
        ~client();
        
        void setIP(std::string ip);
        void setIPbyDNS(std::string ip);
        void setIP(std::string ip, unsigned int port);
        void setIPbyDNS(std::string ip, unsigned int port);
        
        bool setKeepAliveConnection();
        bool setKeepIdleConnection();
        
        virtual int init();
        virtual int sendRequest(HTTP *httpRequest, Request *request, HTTP *httpResponde, Response *response);
        
        virtual int * getSocket();
    protected:
        std::string endpoint;
        
    };

}

#endif /* CLIENT_HPP */

