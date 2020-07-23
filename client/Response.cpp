//
// Created by tinggengyan on 2020/6/25.
//

#include "Response.h"

const Request &Response::getRequest() const {
    return request;
}

void Response::setRequest(const Request &request) {
    Response::request = request;
}

const std::string &Response::getProtocol() const {
    return protocol;
}

void Response::setProtocol(const std::string &aProtocol) {
    protocol = aProtocol;
}

int Response::getCode() const {
    return code;
}

void Response::setCode(int code) {
    Response::code = code;
}

std::string *Response::getHeaders() const {
    return headers;
}

void Response::setHeaders(std::string *headers) {
    Response::headers = headers;
}

int Response::getHeaderLength() const {
    return headerLength;
}

void Response::setHeaderLength(int headerLength) {
    Response::headerLength = headerLength;
}


Response::Response(Request &request) : request(request) {
}

const std::string &Response::getMessage() const {
    return message;
}

void Response::setMessage(const std::string &message) {
    Response::message = message;
}

const Headers &Response::getHeadersMap() const {
    return headersMap;
}

void Response::setHeadersMap(const Headers &headersMap) {
    Response::headersMap = headersMap;
}

size_t Response::getBodSize() const {
    return bodSize;
}

void Response::setBodSize(size_t bodSize) {
    Response::bodSize = bodSize;
}

char *Response::getBody() {
    return body;
}
