/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Response.hpp"
#include <cstdio>
#include <sstream>
#include <cstring>

using namespace WSDL;


/*
 * 
 */
Response::Response()
:p_body(NULL), m_xml(NULL)
{
}


/*
 * 
 */
Response::Response(std::string *s_body)
:p_body(s_body), m_xml(NULL)
{
    m_xml = new xml_document;
    pugi::xml_parse_result result = m_xml->load_buffer(p_body->c_str(), p_body->size());
}


/*
 * 
 */
const std::string Response::getBody()
{
    std::stringstream result;
    this->m_xml->save(result);
    return result.str();
}


/*
 * 
 */
void Response::addNode(const char *nodeName)
{ 
    if(m_xml != NULL)
    {
        const int size = deque_Nodes.size();
        xml_node *p_firstNode;
        xml_node *p_secondNode;
    
        this->deque_Nodes.push_back(xml_node());
        p_firstNode = &deque_Nodes[size];
    
        if(size == 0)
            (*p_firstNode) = m_xml->child(nodeName);
        else
        {
            p_secondNode = &deque_Nodes[size - 1];
            (*p_firstNode) = p_secondNode->child(nodeName);
        }
    }
}


/*
 * 
 */
const char *Response::getLastNodeValue(const char *nodeName)
{
    for (pugi::xml_node tool = deque_Nodes[deque_Nodes.size() - 1].first_child(); tool; tool = tool.next_sibling())
        return tool.child_value();
    
    return NULL;
}


/*
 * 
 */
void Response::clearResponse()
{  
    if(m_xml != NULL)
    {
        m_xml->reset();
        delete m_xml;   
    }
    
    deque_Nodes.clear();
}