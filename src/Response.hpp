/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Responde.hpp
 * Author: madzik
 *
 * Created on March 9, 2019, 1:54 PM
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

