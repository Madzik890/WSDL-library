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

#define CLIENT_MAXRECV_BUFF 65536

namespace WSDL
{

    class client
    {
    private:
        struct sockaddr_in m_service;
        struct timeval tv_sendTime;
        struct timeval tv_recvTime;

        int m_socket;
       
    public:
        client();
        ~client();
        
        void setIP(const char *ip, const unsigned int port = 80);
        void setIPbyDNS(const char *ip, const unsigned int port = 80);
        
        bool setKeepAliveConnection();
        
        int setSendTimeout(const __time_t seconds);
        int setRecvTimeout(const __time_t seconds);
        int setKeepAliveTimeout(const __time_t seconds);
        
        virtual int init();
        virtual int sendRequest(HTTP *httpRequest, Request *request, HTTP *httpResponde, Response *response);
        virtual void close();
        
        virtual int * getSocket();
    protected:
        char * s_endpoint;
        
        const char * getIpByName( const char * hostName );
    };

}

#endif /* CLIENT_HPP */

