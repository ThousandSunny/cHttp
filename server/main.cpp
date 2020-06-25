//
// Created by tinggengyan on 2020/6/20.
//

#include "server.h"
#include "test.h"

int main() {

    // 1. start server
    start_accept(SERVER_PORT);
    start_epoll();

    // 2. start demo Client


    return 0;
}