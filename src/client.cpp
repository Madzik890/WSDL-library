/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "client.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <netinet/tcp.h>
#include <fcntl.h>

#include "Definitions.hpp"

#include "HTTP/HTTP.hpp"
#include "Response.hpp"

using namespace WSDL;


/*
 * Default constructor
 */
client::client()
:tv_sendTime(), tv_recvTime(), s_endpoint(NULL)
{
}


/*
 * Default destructor, always trying to close socket,
 * to not left a blocked port.
 */
client::~client()
{
    shutdown( m_socket, SHUT_RDWR );
}
    

/*
 *
 */
void client::setIP(const char *ip)
{
    if(s_endpoint != NULL)
        delete[] s_endpoint;
        
    size_t ipLength = strlen(ip);
    s_endpoint = new char[ipLength];
    strcpy(s_endpoint, ip);

    m_service.sin_family = AF_INET;
    m_service.sin_addr.s_addr = INADDR_ANY;
    m_service.sin_port = htons( 80 ); // default port to connect HTTP
}


/*
 * 
 */
void client::setIPbyDNS(const char *ip)
{
    const char *dnsIp = getIpByName(ip);
    
    if(dnsIp != NULL)
    {
        if(s_endpoint != NULL)
            delete[] s_endpoint;
    
        size_t ipLength = strlen(dnsIp);
        s_endpoint = new char[ipLength];
        strcpy(s_endpoint, dnsIp);
    
        m_service.sin_family = AF_INET;
        m_service.sin_addr.s_addr = INADDR_ANY;
        m_service.sin_port = htons( 80 ); // default port to connect HTTP
    }
}


/*
 *
 */
void client::setIP(const char *ip, const unsigned int port)
{
    if(s_endpoint != NULL)
        delete[] s_endpoint;
        
    size_t ipLength = strlen(ip);
    s_endpoint = new char[ipLength];
    strcpy(s_endpoint, ip);
    
    m_service.sin_family = AF_INET;
    m_service.sin_addr.s_addr = INADDR_ANY;
    m_service.sin_port = htons( port );
}
   

/*
 * 
 */
void client::setIPbyDNS(const char *ip, const unsigned int port)
{
    const char *dnsIp = getIpByName(ip);
    
    if(dnsIp != NULL)
    {
        if(s_endpoint != NULL)
            delete[] s_endpoint;
        
        size_t ipLength = strlen(dnsIp);
        s_endpoint = new char[ipLength];
        strcpy(s_endpoint, dnsIp);
    
        m_service.sin_family = AF_INET;
        m_service.sin_addr.s_addr = INADDR_ANY;
        m_service.sin_port = htons( port ); // default port to connect HTTP
    }
}


/*
 * Try enable KeepAlive connection with a server.
 * 
 * @return State of setting KeepAlive operation(true - OK, fail - error)
 */
bool client::setKeepAliveConnection()
{
  int flags =1;
  if (setsockopt(m_socket, SOL_SOCKET, SO_KEEPALIVE, (void *)&flags, sizeof(flags))) 
      return false;
  else
      return true;
}
  

/*
 * Set sending timeout.
 * 
 * @param seconds   timeout called in seconds
 */
int client::setSendTimeout(const __time_t seconds)
{
    tv_sendTime.tv_sec = seconds;     /* Timeout in seconds */
    return setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (struct timeval*)&tv_sendTime,sizeof(tv_sendTime));
}


/*
 * Set receiving timeout.
 * 
 * @param seconds   timeout called in seconds
 */
int client::setRecvTimeout(const __time_t seconds)
{
    tv_recvTime.tv_sec = seconds;       /* Timeout in seconds */
    return setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval*)&tv_recvTime,sizeof(tv_recvTime));
}


/*
 * Set max time of keep alive timeout.
 * 
 * @param seconds   timeout called in seconds
 */
int client::setKeepAliveTimeout(const __time_t seconds) 
{
    return setsockopt(m_socket, IPPROTO_TCP, TCP_KEEPCNT, (__time_t*)&seconds, sizeof(seconds)); 
}


/*
 *  Try enable, and reserve socket to selected IP, and port.
 *  If socket would be enabled, return true, else false.
 * 
 *  @return State of whole operation
 */
int client::init()
{   
    if(s_endpoint != NULL)
    {
        inet_pton( m_service.sin_family, s_endpoint, & m_service.sin_addr ); 
        m_socket = socket( m_service.sin_family, SOCK_STREAM, 0 );
    }
    else
        return WSDL_IPNULL_ERROR;
    
    if(m_socket != -1)
        return WSDL_OK;
    else
        return WSDL_SOCKET_ERROR;
}


/*
 * Copy one string to other. 
 * 
 * This function has been created, because "valgrind" said that, 
 * Function "strcat" was not safely in memory operations.
 * 
 * @param string            the string, where will be allocated copy
 * 
 * @param copy              the string, which will be copyied to first argc
 * 
 * @param size              the first size of "copy" string   
 */
void copyString(char * string, const char * copy, size_t size)
{
    size_t firstPos = std::strlen(string);
    
    for(int i = firstPos; i < size; i++)
        string[i] = copy[i - firstPos];
}


/*
 * Try send a request to a server, if request will be correctly provided,
 * will receive a response from a host.
 * 
 * @param httpRequest       the HTTP header
 *  
 * @param request           the request, created by client    
 * 
 * @param httpResponse      the HTTP header, receive from the host 
 * 
 * @param response          the response, get from the server
 * 
 * @return State of whole operation(500 - OK, other code, state of operations
 * is probably not correctly).
 */
int client::sendRequest(HTTP *httpRequest, Request *request, HTTP *httpResponse, Response *response)
{
    if(this->s_endpoint == NULL)
        return WSDL_IPNULL_ERROR;
        
    int error;
    char *s_buffer = NULL;
    size_t i_requestSize = 0;
    
    if(httpRequest != NULL)
    {
        i_requestSize = httpRequest->getBody().size();
        
        s_buffer = (char*) malloc(sizeof(char) * i_requestSize);
        std::memcpy(s_buffer, httpRequest->getBody().c_str(), i_requestSize);
    }
    if(request != NULL)
    {
        i_requestSize += request->getBody().size();
        s_buffer = (char*) realloc (s_buffer, i_requestSize);
        
        copyString(s_buffer, request->getBody().c_str(), i_requestSize);
    }

    
    error = connect( m_socket,( struct sockaddr * ) & this->m_service, sizeof( this->m_service ) );
    if(error == -1)
    {
        delete[] s_buffer;
        return WSDL_CONNECTION_ERROR;
    }
    
    error = send( m_socket, s_buffer, i_requestSize, 0 );
    if(error == -1)
    {
        delete[] s_buffer;
        return WSDL_SEND_ERROR;
    }
    
    std::string s_response;
    char *s_recvBuff = new char[CLIENT_MAXRECV_BUFF]; 
    
    
    while( recv( m_socket, s_recvBuff, CLIENT_MAXRECV_BUFF, 0 ) > 0 )
        s_response += s_recvBuff;
  
    
    if(httpResponse != NULL)
        (*httpResponse) = static_cast<HTTP>(&s_response);
    if(response != NULL)
        (*response) = static_cast<Response>(&s_response);
    
    
    // Clear memory
    if(s_buffer != NULL)
        free(s_buffer);
    if(s_recvBuff != NULL)
        delete[] s_recvBuff;
    s_response.clear();
    
    // Close socket
    shutdown( m_socket, SHUT_RDWR );
    
    if(httpResponse != NULL && httpResponse->getHttpCode() != WSDL_OK)
        return httpResponse->getHttpCode();

    return WSDL_OK;
}


/*
 * Clear all allocated objects from memory.
 */
void client::close()
{
    shutdown( m_socket, SHUT_RDWR );
    
    if(s_endpoint != NULL)
        delete[] s_endpoint;
}


/*
 * Return pointer to the client socket.
 * 
 * @return Pointer to the client socket.
 */
int *client::getSocket()
{
    return &m_socket;
}

/*
 * Get IP of service by name.
 * 
 * @return IP of service, but if not find it, return NULL
 */
const char *client::getIpByName(const char *hostName)
{
    struct hostent * he = NULL;
    
    if(( he = gethostbyname( hostName ) ) == NULL )
        return NULL;
    
    const char * ipAddress;
    ipAddress = inet_ntoa( **( struct in_addr ** ) he->h_addr_list );
    return ipAddress;
}
