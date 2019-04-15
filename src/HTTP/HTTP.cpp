/*
 * Create HTTP header.
 * 
 * In future, I am going to change strings to chars*, 
 * because, each string allocate minimum 24 bytes, which would 
 * give a problem with memory, while using a lot of connections.
 */

#include "HTTP/HTTP.hpp"
#include <cstdio>
#include <sstream>
#include <cstdlib>

using namespace WSDL;

//  Methods
#define HTTP_GET        "GET / "
#define HTTP_POST       "POST / "
//  Versions
#define HTTPVER_1_1     "HTTP/1.1"
#define HTTPVER_1_2     "HTTP/1.2"
//  Security
#define HTTPAUTH_BASIC  "Authorization: Basic "


#define DEFAULT_USER_AGENT "https://github.com/Madzik890"
#define DEFAULT_HTTP_CODE 200

/*
 * Default constructor 
 */
HTTP::HTTP()
:s_buffer(std::string()), s_userAgent(DEFAULT_USER_AGENT),i_httpCode(DEFAULT_HTTP_CODE), p_recBuffer(NULL),
        e_encoding(length), e_connection(close)
{
}


/*
 * Constructor is used by "client" class, while receiving data from a server.@
 * 
 * @param httpHeader            the pointer, to data received from a server
 */
HTTP::HTTP(std::string *httpHeader)
:s_buffer(), s_userAgent(DEFAULT_USER_AGENT), p_recBuffer(httpHeader), e_connection(close)
{
    analizeHeader();
}


/*
 * Default destructor.
 * 
 * In the future, there may be something.
 */
HTTP::~HTTP()
{
}
 

/*
 * Set major parameters of HTTP connections(HTTP method, version and optionaly location resource).
 * 
 * @param method            the method of connection(default POST)
 * 
 * @param version           the version of connection, now supported is only 1.1 and 1.2
 * 
 * @param methodLocation    the location of requested resource, but this is default. You can use it.
 */
void HTTP::setMethod(const enum httpMethod method, const enum httpVersion version, const std::string methodLocation)
{
    this->e_method = method;
    this->e_version = version;
    if(methodLocation != std::string())
        this->e_methodLocation = methodLocation;
}


/*
 *
 */
void HTTP::setIP(const std::string IP)
{
    this->s_IP = IP;
}


/*
 * 
 */
void HTTP::setLengthOfRequest(const unsigned int length)
{
    this->u_contentLenght = length;
}


/*
 *
 */
void HTTP::setSOAPAction(const std::string action)
{
    this->s_soapAction = action;
}


/*
 *
 */
void HTTP::addContentType(const std::string content)
{
    this->s_contentType += content;
}


/*
 * 
 */
void HTTP::setConnectionType(httpConnectionType type)
{
    this->e_connection = type;
}


/*
 * 
 */
void HTTP::setEncodingType(httpDataEncoding encoding)
{
    this->e_encoding = encoding;
}


/*
 * Create HTTP header.
 */
const std::string HTTP::getBody()
{
    std::string s_header;
    
    s_header += this->getMethodTypeString();
    s_header += this->getHostString();
    s_header += this->getUserAgentString();
    s_header += this->getContentTypeString();
    s_header += this->getContentLengthString();
    s_header += this->getConnectionTypeString();
    s_header += this->getSOAPActionString();
    
    /*if(!m_addonVector.empty())
    {
        for(int i = 0; i < m_addonVector.size(); i++)
            s_header += (*m_addonVector[i]);
    }*/
    
    
    s_header += "\n";
    return s_header;
}


/*
 * 
 */
const unsigned int HTTP::getContentLenght()
{
    return this->u_contentLenght;
}


/*
 * 
 */
const enum httpMethod HTTP::getMethod()
{
    return this->e_method;
}


/*
 * 
 */
const enum httpVersion HTTP::getVersion()
{
    return this->e_version;
}


/*
 * 
 */
const enum httpConnectionType HTTP::getConnectionType()
{
    return this->e_connection;
}


/*
 * 
 */
const std::string HTTP::getIP()
{
    return this->s_IP;
}


/*
 * 
 */
const std::string HTTP::getContentType()
{
    return this->s_contentType;
}


/*
 * 
 */
const std::string HTTP::getBuffer()
{
    return this->s_buffer;
}


/*
 * 
 */
const int HTTP::getHttpCode()
{
    return this->i_httpCode;
}
        

/*
 * 
 */
const std::string HTTP::getHttpMessage()
{
    return this->s_httpMess;
}

/*
 * Add a HTTP parameter, which is uses in creating header.
 * 
 * @param param     parameter is pointer to a std::string object
 */
//void HTTP::addHttpParam(httpParam *param)
//{
//    m_addonVector.push_back(param);
//}


//////////////////////////////////////
// HTTP'S HEADER CREATING FUNCTIONS //
//////////////////////////////////////
const std::string HTTP::getMethodTypeString()
{   
    std::string s_result;
    switch(this->e_method)
    {
        case GET:
            s_result += "GET /";
            break;
            
        case POST:
            s_result += "POST /";
            break;
        
        default:
            s_result += "POST /";
            break;
    }
    
    if(e_methodLocation != std::string())
        s_result += e_methodLocation;
    s_result += " ";
    switch(this->e_version)
    {
        case HTTP1_1:
            s_result += "HTTP/1.1";
            break;
            
        case HTTP1_2:
             s_result += "HTTP/1.2";
            break;
        
        default:
            s_result += "HTTP/1.1";
            break;
    }
    
    s_result += "\n";
    
    return s_result;
}


const std::string HTTP::getContentTypeString()
{
    std::string s_result;
    
    if(!this->s_contentType.empty())
    {
        s_result = "Content-Type: ";
        s_result += this->s_contentType;
        s_result += "\n";
    }
    return s_result;
}


const std::string HTTP::getHostString()
{
    std::string s_result;
    
    if(!this->s_IP.empty())
    {
        s_result = "Host: ";
        s_result += this->s_IP;
        s_result += "\n";
    }
    
    return s_result;
}


const std::string HTTP::getUserAgentString()
{
    std::string s_result;
    s_result = "User-Agent: ";
    s_result += HTTP::s_userAgent;
    s_result += "\n";
    
    return s_result;
}


const std::string HTTP::getContentLengthString()
{
    std::string s_result;
    if(e_encoding == length)
    {
        s_result = "Content-Length: ";
    
        std::stringstream ss;
        ss << this->u_contentLenght;
        s_result += ss.str();
        s_result += "\n";
    }
    else
        s_result = "Transfer-Encoding: chunked\n";
    
    return s_result;
}


const std::string HTTP::getConnectionTypeString()
{
    std::string s_result;
    
    switch(e_connection)
    {
        case close:
            s_result = "Connection: close\n";
            break;
        
        case keep_alive:
            s_result = "Connection: keep-alive\n";
            break;
           
        default:
            s_result = "Connection: close\n";
            break;
    }
   
    return s_result;
}


const std::string HTTP::getBasicAuth()
{
    if(this->s_basicAuth != "")
    {
        std::string result;
    
        result = "Authorization: Basic ";
        result += this->s_basicAuth;
        result += "\n";
        
        return result;
    }
    else
        return "";
}

const std::string HTTP::getSOAPActionString()
{   
    std::string s_result;
    
    s_result = "SOAPAction: ";
    s_result += '"';
    s_result += this->s_soapAction;
    s_result += '"';
    s_result += '\n';
    
    return s_result;
}
//////////////////////////////////////
// HTTP'S HEADER CREATING FUNCTIONS //
//////////////////////////////////////


/*
 *
 */
void HTTP::removeAddons()
{
}


/*
 * 
 */
void HTTP::analizeHeader()
{
    std::istringstream f((*this->p_recBuffer));
    std::string line;    
    while (std::getline(f, line)) 
    {
        if (line == "\n")
            break;
        
        analizeDefaultParam(line);
        analizeAddonParam(line);
        
      
        size_t m = this->p_recBuffer->find(line);
        size_t n = this->p_recBuffer->find_first_of("\n", m + line.length());
          this->p_recBuffer->erase(m, n - m + 1);
        //s_buffer.erase(firstNL, secondNL - firstNL + 1);
    }
    //p_rec.clear();
}


/*
 *
 */
void HTTP::analizeDefaultParam(const std::string line)
{
    if(line.find("HTTP/1.1") != std::string::npos || line.find("HTTP/1.2") != std::string::npos)
    {
        const char * errorCode = line.substr(9 , 3).c_str();
        
        this->i_httpCode = std::atoi(errorCode);
        s_httpMess = line.substr(12, line.size());
    }
    else
    if(line.find("Server: ") != std::string::npos)
        this->s_serverName = line.substr(8 , line.size() - 1);
    else
    if(line.find("Content-Type: ") != std::string::npos)
        this->s_contentType = line.substr(14 , line.size() - 1);
    else
    if(line.find("Content-Length: ") != std::string::npos)
    {
        const char * length = line.substr(16 , line.size() - 1).c_str();
        this->u_contentLenght = std::atoi(length);
    }
    
}


/*
 * 
 */
void HTTP::analizeAddonParam(const std::string line)
{
}