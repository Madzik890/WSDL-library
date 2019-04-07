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

#include "Definitions.hpp"

#include "HTTP/HTTP.hpp"
#include "Response.hpp"

using namespace WSDL;


/*
 * 
 */
std::string getIpByName(const char *host) 
{
    hostent* hostname = gethostbyname(host);
    if(hostname)
        return std::string(inet_ntoa(**(in_addr**)hostname->h_addr_list));
    return std::string();
}


/*
 * Default constructor
 */
client::client()
{
}


client::~client()
{
}
    

/*
 *
 */
void client::setIP(std::string ip)
{
    this->endpoint = ip;

    m_service.sin_family = AF_INET;
    m_service.sin_addr.s_addr = INADDR_ANY;
    m_service.sin_port = htons( 80 ); // default port to connect HTTP
}


/*
 * 
 */
void client::setIPbyDNS(std::string ip)
{
    this->endpoint = getIpByName(ip.c_str());

    m_service.sin_family = AF_INET;
    m_service.sin_addr.s_addr = INADDR_ANY;
    m_service.sin_port = htons( 80 ); // default port to connect HTTP
}


/*
 *
 */
void client::setIP(std::string ip, unsigned int port)
{
    this->endpoint = ip;
    
    m_service.sin_family = AF_INET;
    m_service.sin_addr.s_addr = INADDR_ANY;
    m_service.sin_port = htons( port );
}
   

/*
 * 
 */
void client::setIPbyDNS(std::string ip, unsigned int port)
{
    this->endpoint = getIpByName(ip.c_str());

    m_service.sin_family = AF_INET;
    m_service.sin_addr.s_addr = INADDR_ANY;
    m_service.sin_port = htons( port ); // default port to connect HTTP
}


/*
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
 * 
 * @return State of setting KeepIdle operation(true - OK, fail - error)
 */
bool client::setKeepIdleConnection()
{
  int flags = 10;
  if (setsockopt(m_socket, SOL_SOCKET, TCP_KEEPIDLE, (void *)&flags, sizeof(flags))) 
      return false;
  else
      return true;
}
  

/*
 *
 *  @return State of whole operation
 */
int client::init()
{
    inet_pton( m_service.sin_family, endpoint.c_str(), & m_service.sin_addr ); 
    m_socket = socket( m_service.sin_family, SOCK_STREAM, 0 );
    
    if(m_socket != -1)
        return WSDL_OK;
    else
        return WSDL_SOCKET_ERROR;
}


/*
 * Copy
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
 * Return pointer to the client socket.
 * 
 * @return Pointer to the client socket.
 */
int *client::getSocket()
{
    return &m_socket;
}