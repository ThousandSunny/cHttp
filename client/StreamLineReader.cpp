//
// Created by Tinggeng Yan on 2020/7/22.
//

#include <sys/socket.h>
#include <common.h>
#include "StreamLineReader.h"

StreamLineReader::StreamLineReader(int sockFd) : sock_fd(sockFd) {}


void StreamLineReader::readLine(char *buf) {
    int fillIndex = 0;

    for (int i = 0;; ++i) {
        char byte;
        int received = recv(this->sock_fd, &byte, 1, 0);

        if (received < 0) {
            // error
            log("receive error");
            return;
        } else if (received == 0) {
            return;
        }

        buf[fillIndex++] = byte;
        buf[fillIndex] = '\0';
        if (fillIndex > HEADER_LIMIT) {
            log("error index out bound");
        }

        if (byte == '\n') {
            return; //line end
        }

    }
}
