//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_RESPONSE_H
#define CPPHTTP_RESPONSE_H


#include "Request.h"

class Response {
private:
    Request &request;
public:
    Response(Request &request);

private:
    std::string protocol;
    int code;
private:
    std::string *headers;
    int headerLength;
private:
    char *body;

public:
    const Request &getRequest() const;

    void setRequest(const Request &request);

    const std::string &getAProtocol() const;

    void setAProtocol(const std::string &aProtocol);

    int getCode() const;

    void setCode(int code);

    std::string *getHeaders() const;

    void setHeaders(std::string *headers);

    int getHeaderLength() const;

    void setHeaderLength(int headerLength);

    char *getBody() const;

    void setBody(char *body);

};


#endif //CPPHTTP_RESPONSE_H
