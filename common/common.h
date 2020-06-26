//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_COMMON_H
#define CPPHTTP_COMMON_H

#include <iostream>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/socket.h>

#include "netinet/in.h"
#include "sys/socket.h"

#include <ctype.h>
#include <stdio.h>

#include <string>


static void log(const std::string msg) {
    std::cout << msg << std::endl;
}


#endif //CPPHTTP_COMMON_H
