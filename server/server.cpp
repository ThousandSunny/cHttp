//
// Created by tinggengyan on 2020/6/20.
//

#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

// 服务端监听的端口号
#define SERVER_PORT 9090

// 服务端监听的socket
int accept_socket;

// 服务端监听socket的地址
struct sockaddr_in serv_addr;

// epoll 创建的 fd
int epoll_fd;

void start_accept() {

    printf("accept socket starting\n");

    // 1. 启动监听的 socket
    accept_socket = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_PORT);

    // 将socket和本地的地址绑定
    bind(accept_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // 准备等到建立连接
    listen(accept_socket, 20);

    printf("accept socket complete\n");
}

// 新建连接
void new_connect(int fd) {
    printf("新建连接 fd: %d\n", fd);

    // 向 epoll 中注册新建的连接
    struct epoll_event register_child_event;
    register_child_event.events = EPOLLIN;
    register_child_event.data.fd = fd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &register_child_event);

    printf("新建连接 fd: %d 结束\n", fd);
}

// 读取连接套接字中的数据
void read_content(int fd) {
    char buf[1024];
    int bytes = read(fd, buf, 1024);

    if (bytes == 0) {
        printf("连接 %d 关闭\n", fd);
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
        close(fd);
    } else {

        printf("处理 fd: %d 的数据 \n", fd);

        for (int j = 0; j < bytes; j++) {
            // 处理数据
            buf[j] = toupper(buf[j]);
        }

        write(fd, buf, bytes);
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

    struct epoll_event ready_events[1024];
    printf("prepare to while \n");

    for (;;) {
        // 检查是否有准备就绪的事件, -1 表示阻塞,没有就绪的,将一直等待;
        // TODO 试下非阻塞的效果
        printf("epoll_wait..\n");
        size_t ready_size = epoll_wait(epoll_fd, ready_events, 1024, -1);

        for (int i = 0; i < ready_size; i++) {
            // 监听套接字有输入事件,说明有连接的请求
            if (ready_events[i].data.fd == accept_socket) {
                struct sockaddr_in child_addr;
                socklen_t child_addr_len = sizeof(child_addr);
                int new_conn_fd = accept(accept_socket, (struct sockaddr *) &child_addr,
                                         &child_addr_len);
                new_connect(new_conn_fd);
            } else {
                read_content(ready_events[i].data.fd);
            }
        }
    }
}
