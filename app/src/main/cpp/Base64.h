//
// Created by pengfei.guo on 2021/12/8.
//


#ifndef BASE_64_H
#define BASE_64_H
#include <string>
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
#endif
