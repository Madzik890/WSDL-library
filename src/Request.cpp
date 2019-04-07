/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Request.hpp"
#include <cstring>

using namespace WSDL;

/*
 * 
 */        
const std::string Request::getBody()
{ 
    std::stringstream result;
    m_xml.save(result);
    return result.str();
}


/*
 * 
 */
void Request::startXML(const char *version, const char *encoding)
{
     // add a custom declaration node
    pugi::xml_node decl = m_xml.prepend_child(pugi::node_declaration);
    decl.append_attribute("version") = version;
    decl.append_attribute("encoding") = encoding;
}


/*
 * 
 */
void Request::createNamespace(const char *envelopeTag, namespaces namespaces[])
{
    m_root = m_xml.append_child(envelopeTag);
    int i = 0;
    while(namespaces[i].attr.c_str() != NULL && namespaces[i].param.c_str() != NULL)
    {
        m_root.append_attribute(namespaces[i].attr.c_str()) = namespaces[i].param.c_str();
        i++;
    }
}


/*
 * 
 */
void Request::createBody(const char *bodyTag, const char *encodingTag, const char *encodingType)
{
    m_body = m_root.append_child(bodyTag);
    if(encodingTag != NULL && encodingType != NULL)
        m_body.append_attribute(encodingTag) = encodingType;
}


/*
 *
 */
void Request::createRequest(const char *request)
{
    m_request = m_body.append_child(request);
}


/*
 *
 */
template<class Argc>
void Request::addRequestParam(const char* param, const Argc argc)
{
   xml_node m_param = m_request.append_child( param);
   std::stringstream ss; 
   ss << argc;
   m_param.append_child(pugi::node_pcdata).set_value(ss.str().c_str());
}


template void Request::addRequestParam<size_t>(const char*,size_t); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<int>(const char*,int); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<double>(const char*,double); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<float>(const char*,float); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<char>(const char*,char); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<char*>(const char*,char*); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<const char*>(const char*, const char*); // instantiates addRequestParam<int>(int)




