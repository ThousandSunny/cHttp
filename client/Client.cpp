//
// Created by tinggengyan on 2020/6/21.
//

#include "Client.h"
#include <string.h>

int Client::connect_server(std::string server, int port) {
    int sfd;
    struct sockaddr_in server_addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    inet_pton(AF_INET, server.data(), &server_addr.sin_addr);

    int c_rt = connect(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (c_rt < 0) {
        log("connect fail");
    }
    return sfd;
}


void Client::send_data(int sfd, const char *data, int length) {
    int remain = length;
    const char *cp = data;

    while (remain) {
        int written = send(sfd, cp, remain, 0);

        log("have write length" + std::to_string(written) + " data");

        if (written < 0) {
            log("writing occurs error");
            return;
        }

        remain -= written;
        cp += written;
    }
}

void Client::on_socket_can_read(int sfd) {
    char buf[1024];
    int n = read(sfd, buf, 1024);
    if (n == 0) {
        log("[Client]:connection fd(" + std::to_string(sfd) + ") closed");
        return;
    }

    log("[Client]: read content is:" + std::string(buf, n));
}

