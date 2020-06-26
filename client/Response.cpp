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

const std::string &Response::getAProtocol() const {
    return protocol;
}

void Response::setAProtocol(const std::string &aProtocol) {
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

char *Response::getBody() const {
    return body;
}

void Response::setBody(char *body) {
    Response::body = body;
}
