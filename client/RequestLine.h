//
// Created by Tinggeng Yan on 2020/7/21.
//

#ifndef CPPHTTP_REQUESTLINE_H
#define CPPHTTP_REQUESTLINE_H


#include <string>
#include "Request.h"

class RequestLine {
public:
    std::string get(Request request);
};


#endif //CPPHTTP_REQUESTLINE_H
