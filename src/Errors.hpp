/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Errors.hpp
 * Author: madzik
 *
 * Created on March 7, 2019, 10:08 PM
 */

#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>

#define WSDL_ERROR_NONE 0x00000

namespace WSDL
{   
    struct Error
    {
        Error()
        :i_error(0), s_error(std::string("Successful"))
        {
        }
        
        int i_error;
        std::string s_error;
    }
}

#endif /* ERRORS_HPP */

