//
// Created by tinggengyan on 2020/6/26.
//

#ifndef CPPHTTP_URL_H
#define CPPHTTP_URL_H


#include <string>

class Url {
private:
    std::string host;

private:
    std::string path;
    int port;

public:
    const std::string &getHost() const;

    const std::string &getPath() const;

    int getPort() const;

    const std::string getQuery();

public:
    Url(const std::string &host, const std::string &path, int port);

};


#endif //CPPHTTP_URL_H
