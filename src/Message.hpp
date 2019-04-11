#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace WSDL
{
    /*
     *  Mainly class, used to inheritance. 
     * "Request" and "Responde" classes using this class.
     */
    class Message
    {
    public:
        virtual const std::string getBody() = 0;    //pure class
    };
        
}

#endif /* MESSAGE_HPP */

