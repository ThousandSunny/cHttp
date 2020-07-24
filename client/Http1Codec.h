//
// Created by Tinggeng Yan on 2020/7/21.
//

#ifndef CPPHTTP_HTTP1CODEC_H
#define CPPHTTP_HTTP1CODEC_H


#include "HttpCodec.h"
#include "StatusLine.h"
#include "HttpCommon.h"

namespace Http1 {
    class Http1Codec : HttpCodec {

    public:
        Http1Codec(int sockFd);

        void writeRequest(Request request) override;

        StatusLine readHeaderLine() override;

        void readBody(char *bodyBuffer, size_t *size) override;

        Headers readHeaders() override;

    };
}


#endif //CPPHTTP_HTTP1CODEC_H
