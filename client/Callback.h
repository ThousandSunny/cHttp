//
// Created by tinggengyan on 2020/6/25.
//

#ifndef CPPHTTP_CALLBACK_H
#define CPPHTTP_CALLBACK_H


#include "common.h"
#include "Response.h"

class Call;

class Callback {
public:

    virtual void onFailure(Call call);

    virtual void onSuccess(Call call, Response response);

};


#endif //CPPHTTP_CALLBACK_H
