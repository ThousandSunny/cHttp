//
// Created by Tinggeng Yan on 2020/7/21.
//

#ifndef CPPHTTP_STATUSLINE_H
#define CPPHTTP_STATUSLINE_H

#include <string>

class StatusLine {

private:
    int code;
    std::string message;
    std::string protocol;
public:
    const std::string &getProtocol() const;

    int getCode() const;

    const std::string &getMessage() const;

public:
    StatusLine(const std::string &protocol, int code, const std::string &message);

};


#endif //CPPHTTP_STATUSLINE_H
