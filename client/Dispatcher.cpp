//
// Created by Tinggeng Yan on 2020/6/26.
//

#include "Dispatcher.h"
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <vector>

#ifndef   NI_MAXHOST
#define   NI_MAXHOST 1025
#endif

std::vector<const char *> resolveHost(const char *host) {
    std::vector<const char *> ips;

    struct addrinfo *result;
    struct addrinfo *res;
    struct addrinfo hints;
    int error;

    // 初始化
    bzero(&hints, sizeof(hints)); // 确保 struct 为空
    hints.ai_flags = AI_PASSIVE; // 帮我填好我的 IP
    hints.ai_family = AF_UNSPEC; // 不用管是 IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // 解析host,结果以链表的形式保存在result中
    error = getaddrinfo(host, nullptr, &hints, &result);
    if (error != 0) {
        if (error == EAI_SYSTEM) {
            log("getaddrinfo");
        } else {
            std::cout << "error in getaddrinfo: " << gai_strerror(error) << std::endl;
        }
        return ips;
    }

    /* 循环取出结果 */
    for (res = result; res != nullptr; res = res->ai_next) {
        char hostname[NI_MAXHOST];
        error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, NI_MAXHOST, nullptr, 0, 0);
        if (error != 0) {
            std::cout << "error in getnameinfo: " << gai_strerror(error) << std::endl;
            continue;
        }
        if (*hostname != '\0') {
            std::cout << "ip: " << hostname << std::endl;
            ips.push_back(hostname);
        }
    }
    freeaddrinfo(result);
    return ips;
}

Response *Dispatcher::execute(Request request) {

    const Url &url = request.getUrl();
    std::cout << "Dispatcher execute request:" << url.getHost() << std::endl;

    // 1. dns resolve
    const std::vector<const char *> &ips = resolveHost(url.getHost().data());
    unsigned long size = ips.size();
    if (size < 1) {
        log("dns resolve failure,not find ip");
        return nullptr;
    }
    std::cout << "resolve ,ip size: " << size << std::endl << std::endl;
    // 2. connect socket and hold the socket
    const char *ip = ips.at(0);


    Response *response = new Response(request);
    response->setCode(200);
    return response;
}
