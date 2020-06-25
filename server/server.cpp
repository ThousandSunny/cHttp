//
// Created by tinggengyan on 2020/6/20.
//

#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>
#include "common.h"

// 服务端监听的socket
int accept_socket;

// 服务端监听socket的地址
struct sockaddr_in serv_addr;

// epoll 创建的 fd
int epoll_fd;

void start_accept(int port) {
    // 1. 启动监听的 socket
    accept_socket = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    // 将socket和本地的地址绑定
    bind(accept_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // 准备等到建立连接
    listen(accept_socket, 20);

    log("accept socket complete,start accept,now can receive connection request");
}

// 新建连接
void on_new_connect(int fd) {
    // 向 epoll 中注册新建的连接
    struct epoll_event register_child_event;
    register_child_event.events = EPOLLIN;
    register_child_event.data.fd = fd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &register_child_event);

    log("new connection on fd(" + std::to_string(fd) + ") has been added to epoll:");
}

void write_response_to_client(int sfd, const char *res, int res_length) {
    // write back as a result
    write(sfd, res, res_length);
}

void handle_request(int fd, char *req, int req_length) {
    log("read connection fd(" + std::to_string(fd) + ") request : " + std::string(req, req_length));
    // mock response

    char res[req_length];
    for (int j = 0; j < req_length; j++) {
        // 处理数据
        res[j] = toupper(req[j]);
    }

    write_response_to_client(fd, res, req_length);
}

// 读取连接套接字中的数据
void on_connection_can_read(int fd) {
    char buf[1024];
    int bytes = read(fd, buf, 1024);

    if (bytes == 0) {
        log("connection fd(" + std::to_string(fd) + ") closed");
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
        close(fd);
    } else {
        handle_request(fd, buf, bytes);
    }
}

// 创建 epoll 监听 socket
void start_epoll() {
    // 创建一个epoll实例
    epoll_fd = epoll_create(1024);

    // 向epoll中注册的事件
    struct epoll_event register_accept_socket_event;
    register_accept_socket_event.events = EPOLLIN;
    register_accept_socket_event.data.fd = accept_socket; // 告知系统需要监听的 fd;

    // 将对socket的监听,添加到epoll中
    int result = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, accept_socket,
                           &register_accept_socket_event);
    if (result < 0) {
        log("error occurs when add bind socket to epoll");
        return;
    }

    struct epoll_event ready_events[1024];

    for (;;) {
        // 检查是否有准备就绪的事件, -1 表示阻塞,没有就绪的,将一直阻塞等待;
        log("epoll_wait..");
        size_t ready_size = epoll_wait(epoll_fd, ready_events, 1024, -1);

        for (int i = 0; i < ready_size; i++) {
            // 监听套接字有输入事件,说明有连接的请求
            if (ready_events[i].data.fd == accept_socket) {
                struct sockaddr_in child_addr;
                socklen_t child_addr_len = sizeof(child_addr);
                int new_conn_fd = accept(accept_socket,
                                         (struct sockaddr *) &child_addr,
                                         &child_addr_len);
                on_new_connect(new_conn_fd);
            } else {
                on_connection_can_read(ready_events[i].data.fd);
            }
        }
    }
}
