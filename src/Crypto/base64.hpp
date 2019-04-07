/*
 * Contains functions encoding and decoding data in base64 format.
 * To works is used OpenSSL library.
 */

/* 
 * File:   base64.hpp
 * Author: madzik
 *
 * Created on March 6, 2019, 7:34 PM
 */

#ifndef BASE64_HPP
#define BASE64_HPP

#include <string>

void base64Encode(const std::string input, std::string *output);
void base64Decode(const std::string input, std::string *output);

#endif /* BASE64_HPP */

