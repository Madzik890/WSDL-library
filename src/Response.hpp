/*
 * SOAP Response
 */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Message.hpp"
#include "pugixml/pugixml.hpp"
#include <deque>


using namespace pugi;

namespace WSDL
{
    class Response
    :public WSDL::Message
    {
    public:
        explicit Response();
        Response(std::string *s_body);
        
        virtual const std::string getBody();
        
        void addNode(const char *nodeName);
        const char *getLastNodeValue(const char *nodeName);
        
        void clearResponse();

    protected:
        xml_document *m_xml;
        
      
        std::deque<xml_node>deque_Nodes;
        std::string *p_body;//pointer to 
        
        void clearNodes();
    };
}

#endif /* RESPONDE_HPP */

