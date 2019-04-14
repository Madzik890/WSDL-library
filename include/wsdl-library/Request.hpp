/*
 * SOAP Request
 */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Message.hpp"
#include "namespaces.hpp"
#include "pugixml/pugixml.hpp"
#include <fstream>
#include <sstream>


using namespace pugi;

namespace WSDL
{
    class Request
    :public WSDL::Message
    {
    private:
        template <typename I>
        std::string n2hexstr(I w, size_t hex_len = sizeof(I)<<1);
        
    public:
        Request();
        
        virtual const std::string getBody();
        
        void startXML(const char *version, const char *encoding);
        void createNamespace(const char *envelopeTag, namespaces namespaces[]);
        void createBody(const char *bodyTag, const char *encodingTag = NULL, const char *encodingType = NULL);
        void createRequest(const char *request);
        
        template<class Argc>
        void addRequestParam(const char* param, Argc argc);
        void setChunked(bool chunked);
        
        bool isChunked();
    protected:
        bool b_chunked;
        
        xml_document m_xml;
        xml_node m_root;
        xml_node m_body;
        xml_node m_request;
    };
}

#endif /* REQUEST_HPP */

