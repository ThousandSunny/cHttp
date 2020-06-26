//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_HTTPCLIENT_H
#define CPPHTTP_HTTPCLIENT_H

#include "Request.h"
#include "Call.h"

/**
 *
 * 负责发送 http 请求,该类最好做成单例;
 * 1. 生产网络请求 call;
 * 2. 持有连接池;
 * 3. 持有线程池;
 *
 */
class HttpClient {

public:
    Call *newCall(Request *request, HttpClient *client);
};


#endif //CPPHTTP_HTTPCLIENT_H
