//
// Created by Tinggeng Yan on 2020/6/26.
//

#include "Dispatcher.h"

Response *Dispatcher::execute(Request request) {

    std::cout << "Dispatcher execute request:" << request.getUrl().getHost() << std::endl;

    Response *response = new Response(request);
    response->setCode(200);
    return response;
}
