//
// Created by Tinggeng Yan on 2020/6/26.
//

#include "Dispatcher.h"

void Dispatcher::execute(Request request) {

    std::cout << "Dispatcher execute request:" << request.getUrl().getHost() << std::endl;

}
