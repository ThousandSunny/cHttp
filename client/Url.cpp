//
// Created by tinggengyan on 2020/6/26.
//

#include "Url.h"

Url::Url(const std::string &host, const std::string &path, int port) : host(host), path(path), port(port) {}

const std::string &Url::getHost() const {
    return host;
}

const std::string &Url::getPath() const {
    return path;
}

int Url::getPort() const {
    return port;
}
