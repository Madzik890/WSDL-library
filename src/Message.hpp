/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.hpp
 * Author: madzik
 *
 * Created on March 7, 2019, 9:37 PM
 */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace WSDL
{
    class Message
    {
    public:
        virtual const std::string getBody() = 0;
    };
        
}

#endif /* MESSAGE_HPP */
