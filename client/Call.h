//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_CALL_H
#define CPPHTTP_CALL_H

#include "Response.h"
#include "Callback.h"
#include "Dispatcher.h"

class Call {
private:
    Request *request;
    Dispatcher &dispatcher;
public:
    Response *execute();

    void enqueue(Callback resCallback);

    bool isExecuted();

    bool isCanceled();

    Call(Request *pRequest, Dispatcher &dispatcher);
};


#endif //CPPHTTP_CALL_H
