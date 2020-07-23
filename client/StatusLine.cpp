//
// Created by Tinggeng Yan on 2020/7/21.
//

#include "StatusLine.h"

StatusLine::StatusLine(const std::string &protocol, int code, const std::string &message) : code(code),
                                                                                            protocol(protocol),
                                                                                            message(message) {
}

const std::string &StatusLine::getProtocol() const {
    return protocol;
}

int StatusLine::getCode() const {
    return code;
}

const std::string &StatusLine::getMessage() const {
    return message;
}
