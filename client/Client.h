//
// Created by tinggengyan on 2020/6/21.
//

#ifndef CPPHTTP_CLIENT_H
#define CPPHTTP_CLIENT_H

#include "common.h"

class Client {
public:

    int connect_server(std::string server, int port);

    void send_data(int sfd, const char *data, int length);

    void on_socket_can_read(int sfd);
};


#endif //CPPHTTP_CLIENT_H
