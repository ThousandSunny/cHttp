//
// Created by tinggengyan on 2020/6/20.
//

#include "Client.h"
#include "test.h"

#include "HttpClient.h"

int main() {

//    Client client;
//    int sfd = client.connect_server(SERVER_HOST, SERVER_PORT);
//    std::string msg = "steveyan";
//    client.send_data(sfd, msg.data(), msg.size());
//    client.on_socket_can_read(sfd);


    HttpClient httpClient;
    Url url("taobao", "/path", 8080);
    Request request(url);
    Call *call = httpClient.newCall(&request);
    Response *res = call->execute();
    std::cout << res->getCode();

    return 0;
}