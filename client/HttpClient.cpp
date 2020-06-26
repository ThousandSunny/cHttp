//
// Created by tinggengyan on 2020/6/25.
//

#include "HttpClient.h"

Call *HttpClient::newCall(Request *request, HttpClient *client) {

    Call call(request);

    call.execute();
    return &call;
}


