//
// Created by tinggengyan on 2020/6/20.
//

#include "Client.h"
#include "test.h"

#include "HttpClient.h"
#include "../third/log/loguru.h"
int main() {

//    Client client;
//    int sfd = client.connect_server(SERVER_HOST, SERVER_PORT);
//    std::string msg = "steveyan";
//    client.send_data(sfd, msg.data(), msg.size());
//    client.on_socket_can_read(sfd);

//    LOG_SCOPE_FUNCTION(INFO);
    LOG_F(INFO, "Doing some stuff...");

    HttpClient httpClient;
    Url url("www.qq.com", "/", 8080);
    Request request(url);
    request.setMethod("GET");
    Call *call = httpClient.newCall(&request);
    Response *res = call->execute();


    std::cout << "返回的 response status line: " << std::endl;
    std::cout << "  code: " << res->getCode() << std::endl;
    std::cout << "  msg: " << res->getMessage() << std::endl;
    std::cout << "  protocol: " << res->getProtocol() << std::endl;

    std::cout << "返回的 response header: " << std::endl;

    auto headersMap = res->getHeadersMap();

    for (auto it = headersMap.begin(); it != headersMap.end(); it++) {
        std::cout << "  " << it->first << " > " << it->second << std::endl;
    }

    std::cout << "返回的 response body: " << std::endl;
    const char *body = res->getBody();
    size_t bodSize = res->getBodSize();
    std::cout << std::string(body, bodSize) << std::endl;


    return 0;
}