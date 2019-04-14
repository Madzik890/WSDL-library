/*
 * SOAP Request
 */

#include "Request.hpp"
#include <cstring>

using namespace WSDL;

template <typename I> 
std::string Request::n2hexstr(I w, size_t hex_len) 
{
    static const char* digits = "0123456789ABCDEF";
    std::string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}


Request::Request()
:b_chunked(false)
{   
}

/*
 * Return the request body.
 * 
 * @return Body of Request.
 */        
const std::string Request::getBody()
{ 
    std::stringstream result;
    if(b_chunked)
    {
        m_xml.save(result);
        std::string xml = result.str();
        result.str("");
        result.clear();
        
        result << n2hexstr<int>(xml.size() - 1) + "\n";
        result << xml;
        result << "0\n\n";
    }
    else
        m_xml.save(result);
    
    return result.str();
}


/*
 * Start work with XML, setting version and encoding of the XML file.
 * 
 * @param version   XML version
 * 
 * @param encoding  XML encoding
 */
void Request::startXML(const char *version, const char *encoding)
{
     // add a custom declaration node
    pugi::xml_node decl = m_xml.prepend_child(pugi::node_declaration);
    decl.append_attribute("version") = version;
    decl.append_attribute("encoding") = encoding;
}


/*
 * Add namespaces to request, if service requires it.
 * 
 * @parma envelopeTag   the envelope tag
 * 
 * @param namespaces    the array with namespaces
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
 * Create body of request.
 * 
 * @param bodyTag       the body tag
 * 
 * @param encodingTag   the encoding tag    
 * 
 * @param encodingType  the encoding type
 */
void Request::createBody(const char *bodyTag, const char *encodingTag, const char *encodingType)
{
    m_body = m_root.append_child(bodyTag);
    if(encodingTag != NULL && encodingType != NULL)
        m_body.append_attribute(encodingTag) = encodingType;
}


/*
 * Create request.
 * 
 * @param request   the request tag 
 */
void Request::createRequest(const char *request)
{
    m_request = m_body.append_child(request);
}


/*
 *  Add a parameter to the request.
 *  This function is adjusted to works with differents type of variable.
 * 
 * @param param     the parameter in XML request, which has a arguments
 * 
 * @param argc      the argument connected with the parameter
 */
template<class Argc>
void Request::addRequestParam(const char* param, const Argc argc)
{
   xml_node m_param = m_request.append_child( param);
   std::stringstream ss; 
   ss << argc;
   m_param.append_child(pugi::node_pcdata).set_value(ss.str().c_str());
}


/*
 * 
 */
void Request::setChunked(bool chunked)
{
    this->b_chunked = chunked;
}

/*
 * 
 */
bool Request::isChunked()
{
    return b_chunked;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template void Request::addRequestParam<size_t>(const char*,size_t); // instantiates addRequestParam<size_t>(size_t)
template void Request::addRequestParam<int>(const char*,int); // instantiates addRequestParam<int>(int)
template void Request::addRequestParam<double>(const char*,double); // instantiates addRequestParam<double>(double)
template void Request::addRequestParam<float>(const char*,float); // instantiates addRequestParam<float>(float)
template void Request::addRequestParam<char>(const char*,char); // instantiates addRequestParam<char>(char)
template void Request::addRequestParam<char*>(const char*,char*); // instantiates addRequestParam<char*>(char*)
template void Request::addRequestParam<const char*>(const char*, const char*); // instantiates addRequestParam<const char*>(const char*)




