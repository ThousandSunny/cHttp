//
// Created by Tinggeng Yan on 2020/7/21.
//

#ifndef CPPHTTP_HTTPCODEC_H
#define CPPHTTP_HTTPCODEC_H


#include "Request.h"
#include "StatusLine.h"
#include "HttpCommon.h"

// 目前将所有的数据一次性读入内存,后面可以改成环状缓存

class HttpCodec {
protected:
    int sock_fd;
public:
    HttpCodec(int sockFd);

public:

    virtual void writeRequest(Request request) = 0;

    virtual StatusLine readHeaderLine() = 0;

    virtual Headers readHeaders() = 0;

    virtual void readBody(char *bodyBuffer, size_t *size) = 0;

};


#endif //CPPHTTP_HTTPCODEC_H
