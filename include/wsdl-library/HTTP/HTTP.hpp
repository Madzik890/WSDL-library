/*
 * Create HTTP header.
 * 
 * In future, I am going to change strings to chars*, 
 * because, each string allocate minimum 24 bytes, which would 
 * give a problem with memory, while using a lot of connections.
 */

#ifndef HTTP_HPP
#define HTTP_HPP

#include <string>
#include <vector>


enum httpVersion
{
    HTTP1_1 = 0x11,
    HTTP1_2 = 0x12
};
  

enum httpMethod
{
    GET = 0x1,
    POST = 0x2
};


enum httpDataEncoding
{
    length = 0x101,
    chunked = 0x102
};


enum httpConnectionType
{
    close = 0x201,
    keep_alive = 202
};

typedef char* httpParam;

namespace WSDL
{
    /*
     * Creates the HTTP header, added in top of WSDL request.
     * List with the HTTP_addon is used to add new HTTP options, 
     * which were not thought.
     */
    class HTTP
    {
    private:
        const char *s_userAgent;
        //std::vector<httpParam*>m_addonVector;
        
    public:
        HTTP();
        explicit HTTP(std::string *httpHeader);
        ~HTTP();
        
        void setMethod(const enum httpMethod method, const enum httpVersion version, const std::string methodLocation = std::string());//sets type of method and version of connection
        void setIP(const std::string IP);
        void setLengthOfRequest(const unsigned int length);
        void setSOAPAction(const std::string action);
        void addContentType(const std::string);
        void setConnectionType(httpConnectionType type);
        void setEncodingType(httpDataEncoding encoding);
        
        virtual const std::string getBody();//returns finished header
        
        const unsigned int getContentLenght();
        const enum httpMethod getMethod();
        const enum httpVersion getVersion();
        const enum httpDataEncoding getEncodingType();
        const enum httpConnectionType getConnectionType();
        const std::string getIP();
        const std::string getContentType();
        const std::string getBuffer();
        
        const int getHttpCode();
        const std::string getHttpMessage();
       
        //void addHttpParam(httpParam *param);
    protected:
        void removeAddons();//removes 
        void analizeHeader();
        void analizeDefaultParam(const std::string line);
        void analizeAddonParam(const std::string line);
        
        const std::string getMethodTypeString();
        const std::string getContentTypeString();
        const std::string getHostString();
        const std::string getServerName();
        const std::string getUserAgentString();
        const std::string getContentLengthString();
        const std::string getConnectionTypeString();
        const std::string getBasicAuth();
        const std::string getSOAPActionString();
        
        std::string s_buffer;//header of http request
        std::string *p_recBuffer;//pointer used only to analyze received header
        
        ///////////////////////////////////////////
        /// Variables are used to create header ///
        ///////////////////////////////////////////
        unsigned int u_contentLenght;
        enum httpMethod e_method;
        enum httpVersion e_version;
        enum httpDataEncoding e_encoding;
        enum httpConnectionType e_connection;
        std::string e_methodLocation;
        
        std::string s_IP;
        
        std::string s_contentType;
        std::string s_soapAction;
        std::string s_basicAuth;
        ///////////////////////////////////////////
        
        /////////////////////////////////////////
        /// Variables are returned by service ///
        /////////////////////////////////////////
        int i_httpCode;
        std::string s_httpMess;
        
        std::string s_serverName;
        /////////////////////////////////////////
    };
    
}

#endif /* HTTP_HPP */

