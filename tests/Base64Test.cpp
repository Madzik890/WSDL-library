/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Base64Test.cpp
 * Author: madzik
 *
 * Created on March 6, 2019, 8:24 PM
 */

#include <stdlib.h>
#include <iostream>
//#include "src/Crypto/base64.hpp"
#include "../src/Crypto/base64.hpp"

/*
 * Tests of base64 encode and decode.
 */


#define DEFAULT_INPUT "ehferesffffffffffffffffffuiahasdfuihsdauifhsauifhasuidfhsuidafhuieahuiahdfuihasdfui"
#define DEFAULT_RESULT "ZWhmZXJlc2ZmZmZmZmZmZmZmZmZmZmZmZnVpYWhhc2RmdWloc2RhdWlmaHNhdWlmaGFzdWlkZmhzdWlkYWZodWllYWh1aWFoZGZ1aWhhc2RmdWk="

void testBase64Encode() 
{
    const std::string input = DEFAULT_INPUT;
    std::string output;
    base64Encode(input, &output);
    if (output.compare(DEFAULT_RESULT) == 0) 
    {
        std::cout << "%TEST_FAILED% time=0 testname=testBase64Encode (Base64Test) message = error message" << std::endl;
        std::cout << "Input = " << input << " Encoded = "  << output << std::endl;
    }
    else
        std::cout << "Input = " << input << " Encoded = "  << output << std::endl;
}


void testBase64Decode() 
{
    const std::string input = DEFAULT_RESULT;
    std::string output;
    base64Decode(input, &output);
    if (output.compare(DEFAULT_RESULT) == 0) 
    {
        std::cout << "%TEST_FAILED% time=0 testname=testBase64Decode (Base64Test) message=error message" << std::endl;
        std::cout << "Input = " << input << " Decoded = "  << output << std::endl;
    }
    else
        std::cout << "Input = " << input << " Encoded = "  << output << std::endl;
}


int main(int argc, char** argv) 
{
    std::cout << "%SUITE_STARTING% Base64Test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testBase64Encode (Base64Test)" << std::endl;
    testBase64Encode();
    std::cout << "%TEST_FINISHED% time=0 testBase64Encode (Base64Test)" << std::endl;

    std::cout << "%TEST_STARTED% testBase64Decode (Base64Test)" << std::endl;
    testBase64Decode();
    std::cout << "%TEST_FINISHED% time=0 testBase64Decode (Base64Test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

