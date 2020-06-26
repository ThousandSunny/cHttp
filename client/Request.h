//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_REQUEST_H
#define CPPHTTP_REQUEST_H

#include "common.h"
#include "Url.h"

class Request {

private:
    Url url;
    std::string method;

private:

    std::string *headers;
    int headerLength;

private:

    std::string mediaType;
    int bodyLength;
    char *bodySource;

public:
    Request(const Url &url);

public:
    const Url &getUrl() const;

    void setUrl(const Url &url);

    const std::string &getMethod() const;

    void setMethod(const std::string &method);

    std::string *getHeaders() const;

    void setHeaders(std::string *headers);

    int getHeaderLength() const;

    void setHeaderLength(int headerLength);

    const std::string &getMediaType() const;

    void setMediaType(const std::string &mediaType);

    int getBodyLength() const;

    void setBodyLength(int bodyLength);

    char *getBodySource() const;

    void setBodySource(char *bodySource);
};


#endif //CPPHTTP_REQUEST_H
