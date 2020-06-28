//
// Created by tinggengyan on 2020/6/25.
//

#include "HttpClient.h"

Call *HttpClient::newCall(Request *request) {
    Call *call = new Call(request, this->dispatcher);
    return call;
}

void HttpClient::initDefaultConfig() {
    this->dispatcher = Dispatcher();
}

const Dispatcher &HttpClient::getDispatcher() const {
    return dispatcher;
}

HttpClient::HttpClient() {
    this->initDefaultConfig();
}


