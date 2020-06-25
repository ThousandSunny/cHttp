//
// Created by tinggengyan on 2020/6/20.
//

#include "Client.h"
#include "test.h"

int main() {

    Client client;
    int sfd = client.connect_server(SERVER_HOST, SERVER_PORT);
    std::string msg = "steveyan";
    client.send_data(sfd, msg.data(), msg.size());
    client.on_socket_can_read(sfd);
    return 0;
}