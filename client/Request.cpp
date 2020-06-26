//
// Created by tinggengyan on 2020/6/25.
//

#include "Request.h"

Request::Request(const Url &url) : url(url) {}

const Url &Request::getUrl() const {
    return url;
}

void Request::setUrl(const Url &url) {
    Request::url = url;
}

const std::string &Request::getMethod() const {
    return method;
}

void Request::setMethod(const std::string &method) {
    Request::method = method;
}

std::string *Request::getHeaders() const {
    return headers;
}

void Request::setHeaders(std::string *headers) {
    Request::headers = headers;
}

int Request::getHeaderLength() const {
    return headerLength;
}

void Request::setHeaderLength(int headerLength) {
    Request::headerLength = headerLength;
}

const std::string &Request::getMediaType() const {
    return mediaType;
}

void Request::setMediaType(const std::string &mediaType) {
    Request::mediaType = mediaType;
}

int Request::getBodyLength() const {
    return bodyLength;
}

void Request::setBodyLength(int bodyLength) {
    Request::bodyLength = bodyLength;
}

char *Request::getBodySource() const {
    return bodySource;
}

void Request::setBodySource(char *bodySource) {
    Request::bodySource = bodySource;
}
