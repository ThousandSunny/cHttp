//
// Created by Tinggeng Yan on 2020/7/21.
//

#include "Http1Codec.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include <string>
#include <regex>
#include "constant.h"
#include "StreamLineReader.h"

Http1Codec::Http1Codec(int sockFd) : HttpCodec(sockFd) {}

void Http1Codec::writeRequest(Request request) {
    RequestLine requestLine;
    const std::string &reqStr = requestLine.get(request);
    // write req line
    const char *str = reqStr.c_str();
    send(this->sock_fd, str, strlen(str), 0);
    send(this->sock_fd, "\r\n", strlen("\r\n"), 0);

    // write headers
    std::string *headers = request.getHeaders();
    int headerLength = request.getHeaderLength();
    for (int i = 0; i < headerLength - 1; ++i) {

        const char *key = (headers + i)->c_str();
        send(this->sock_fd, key, strlen(key), 0);

        send(this->sock_fd, ": ", strlen(": "), 0);

        const char *value = (headers + i + 1)->c_str();
        send(this->sock_fd, value, strlen(value), 0);


        send(this->sock_fd, "\r\n", strlen("\r\n"), 0);

    }

    // write request finish signal
    send(this->sock_fd, "\r\n", strlen("\r\n"), 0);

}


void oldReadLine() {
    // from outside
    char *buffer;
    int received;

    char *lineEnd = std::find(buffer, buffer + received, '\n');

    unsigned long length = lineEnd - buffer;
    if (length < 0) {
        StatusLine("null", 0, "no line");
    }
    char line[length + 1];
    memcpy(line, buffer, length);
    line[length] = '\0';


    char protocol[9];
    memcpy(protocol, line, 8);
    protocol[8] = '\0';

//    std::cout << "line:" << line << std::endl;

    char codeStr[4];
    memcpy(codeStr, line + 9, 3);
    codeStr[3] = '\0';
    int code = std::stoi(codeStr);


    char message[HEADER_LIMIT];
    memcpy(message, line + 13, length - 13);
    message[length - 12] = '\0';


    const std::string p = std::string(protocol);
    const std::string m = std::string(message);


    StatusLine(p, code, m);
}


StatusLine Http1Codec::readHeaderLine() {
    StreamLineReader reader(this->sock_fd);
    char lineBuffer[HEADER_LIMIT];
    reader.readLine(lineBuffer);


    const static std::regex re("(HTTP/1\\.[01]) (\\d+).*? ([\\S\\s]+)\r\n");
    std::cmatch m;

    std::string p;
    int code = 0;
    std::string message = "message";

    if (std::regex_match(lineBuffer, m, re)) {
        p = std::string(m[1]);
        code = std::stoi(std::string(m[2]));
        message = std::string(m[3]);
    }

    return StatusLine(p, code, message);
}

bool end_with_crlf(char *lineBuffer) {
    int size = strlen(lineBuffer);
    return size >= 2 && lineBuffer[size - 2] == '\r' && lineBuffer[size - 1] == '\n';
}

Headers Http1Codec::readHeaders() {
    StreamLineReader reader(this->sock_fd);
    char lineBuffer[HEADER_LIMIT];


    Headers headers;

    while (true) {
        reader.readLine(lineBuffer);
        size_t length = strlen(lineBuffer);

        if (end_with_crlf(lineBuffer)) {
            if (length == 2) {
                break;
            }
        }

        const static std::regex re("(\\S+): ([\\S\\s]+)\r\n");
        std::cmatch m;

        std::string key, value;
        if (std::regex_match(lineBuffer, m, re)) {
            key = std::string(m[1]);
            value = std::string(m[2]);
        }

        headers.insert(std::pair<std::string, std::string>(key, value));

//        if (end_with_crlf(lineBuffer)) {
//            if (length == 2) {
//                break;
//            }
//        } else {
//            length -= 2;
//            if (length > 0) {
//                int loopSize = length;
//                for (int i = 1; i < loopSize; ++i) {
//                    if (lineBuffer[loopSize - i] == ' ' || lineBuffer[loopSize - i] == '\t') {
//                        length--;
//                    }
//                }
//            }
//        }


    }


    return headers;
}

// 目前假设,body大小不超过
void Http1Codec::readBody(char *bodyBuffer, size_t *size) {
    *size = recv(this->sock_fd, bodyBuffer, MAXBODYSIZE - 1, 0);
    if (*size == -1) {
        std::cout << "read body error" << strerror(errno) << std::endl;
    }
}

