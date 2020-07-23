//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_RESPONSE_H
#define CPPHTTP_RESPONSE_H


#include "Request.h"
#include "HttpCommon.h"
#include "constant.h"

class Response {
private:
    Request &request;
public:
    Response(Request &request);

private:
    std::string protocol;
    int code;
    std::string message;
public:
    const std::string &getMessage() const;

    void setMessage(const std::string &message);

private:
    std::string *headers;
    int headerLength;
    Headers headersMap;
public:
    const Headers &getHeadersMap() const;

    void setHeadersMap(const Headers &headersMap);

private:
    char body[MAXBODYSIZE];
public:
    char *getBody();

private:
    size_t bodSize = 0;

public:
    size_t getBodSize() const;

    void setBodSize(size_t bodSize);

public:
    const Request &getRequest() const;

    void setRequest(const Request &request);

    const std::string &getProtocol() const;

    void setProtocol(const std::string &aProtocol);

    int getCode() const;

    void setCode(int code);

    std::string *getHeaders() const;

    void setHeaders(std::string *headers);

    int getHeaderLength() const;

    void setHeaderLength(int headerLength);

};


#endif //CPPHTTP_RESPONSE_H
