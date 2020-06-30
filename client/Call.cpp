//
// Created by tinggengyan on 2020/6/25.
//

#include "Call.h"

Response *Call::execute() {
    return this->dispatcher.execute(*this->request);
}

void Call::enqueue(Callback resCallback) {

}

bool Call::isExecuted() {
    return false;
}

bool Call::isCanceled() {
    return false;
}

Call::Call(Request *req, Dispatcher &dispatcher) : request(req), dispatcher(dispatcher) {

}

