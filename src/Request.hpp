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
    public:
        virtual const std::string getBody();
        
        void startXML(const char *version, const char *encoding);
        void createNamespace(const char *envelopeTag, namespaces namespaces[]);
        void createBody(const char *bodyTag, const char *encodingTag = NULL, const char *encodingType = NULL);
        void createRequest(const char *request);
        
        template<class Argc>
        void addRequestParam(const char* param, Argc argc);
        
    protected:
        xml_document m_xml;
        xml_node m_root;
        xml_node m_body;
        xml_node m_request;
    };
}

#endif /* REQUEST_HPP */

