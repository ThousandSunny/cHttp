//
// Created by tinggengyan on 2020/6/25.
//

#include "Call.h"

Response *Call::execute() {
    return nullptr;
}

void Call::enqueue(Callback resCallback) {

}

bool Call::isExecuted() {
    return false;
}

bool Call::isCanceled() {
    return false;
}

Call::Call(Request *request) : request(request) {
}
