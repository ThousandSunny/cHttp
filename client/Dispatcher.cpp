//
// Created by Tinggeng Yan on 2020/6/26.
//

#include "Dispatcher.h"
#include "Http1Codec.h"
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <vector>
#include "constant.h"

struct addrinfo *resolveHost(const char *host, int *length) {
    struct addrinfo *result;
    struct addrinfo *res;
    struct addrinfo hints;
    int error;

    // 初始化
    bzero(&hints, sizeof(hints)); // 确保 struct 为空
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = AF_UNSPEC; // 不用管是 IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // 解析host,结果以链表的形式保存在result中
    error = getaddrinfo(host, "80", &hints, &result);
    if (error != 0) {
        if (error == EAI_SYSTEM) {
            log("getaddrinfo");
        } else {
            std::cout << "error in getaddrinfo: " << gai_strerror(error) << std::endl;
        }
        return nullptr;
    }

    /* 循环取出结果 */
    for (res = result; res != nullptr; res = res->ai_next) {
        char *type;
        if (res->ai_family == AF_INET) {  // IPv4
            type = "IPv4";
        } else {// IPv6
            type = "IPv6";
        }

        char hostname[NI_MAXHOST];
        error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, NI_MAXHOST, nullptr, 0, 0);
        if (error != 0) {
            std::cout << "error in getnameinfo: " << gai_strerror(error) << std::endl;
            continue;
        }
        if (*hostname != '\0') {
            std::cout << type << ",ip: " << hostname << std::endl;
        }
        (*length)++;
    }
    return result;
}

Response *Dispatcher::execute(Request request) {

    const Url &url = request.getUrl();
    std::cout << "Dispatcher execute request:" << url.getHost() << std::endl;

    // 1. dns resolve
    int length = 0;
    addrinfo *result = resolveHost(url.getHost().data(), &length);
    if (length < 1) {
        log("dns resolve failure,not find ip");
        return nullptr;
    }
    std::cout << "resolve ,ip size: " << length << std::endl;

    // 2. connect socket and hold the socket
    struct addrinfo *current;

    int sockfd;
    // 寻找能建连的ip
    for (current = result; current != nullptr; current = current->ai_next) {
        if ((sockfd = socket(current->ai_family, current->ai_socktype, current->ai_protocol)) == -1) {
            log("client: error in socket");
            continue;
        }
        if (connect(sockfd, current->ai_addr, current->ai_addrlen) == -1) {
            close(sockfd);
            log("client: error in connect");
            continue;
        }
        break;
    }
    if (current == nullptr) {
        log("fail to connect to any ip");
        freeaddrinfo(result);
        return nullptr;
    }

    char ip[NI_MAXHOST];
    int error = getnameinfo(current->ai_addr, current->ai_addrlen, ip, NI_MAXHOST, nullptr, 0, 0);
    std::cout << "connecting to " << ip << std::endl;
    freeaddrinfo(result);


    Http1::Http1Codec codec(sockfd);
    codec.writeRequest(request);

//    codec.readAll();

    const StatusLine statusLine = codec.readHeaderLine();
    int code = statusLine.getCode();
    const std::string &msg = statusLine.getMessage();
    const std::string &protocol = statusLine.getProtocol();


    const Headers &headers = codec.readHeaders();

    auto *response = new Response(request);
    response->setCode(code);
    response->setRequest(request);
    response->setProtocol(protocol);
    response->setMessage(msg);
    response->setHeadersMap(headers);

    size_t size;
    codec.readBody(response->getBody(), &size);
    response->setBodSize(size);

    close(sockfd);

    return response;
}
