//
// Created by Tinggeng Yan on 2020/7/22.
//

#ifndef CPPHTTP_STREAMLINEREADER_H
#define CPPHTTP_STREAMLINEREADER_H


#include <array>
#include "constant.h"

/**
 * 用于读取一行的数据
 */
class StreamLineReader {
private:
    int sock_fd;
public:
    StreamLineReader(int sockFd);

public:
    void readLine(char *buf);

};


#endif //CPPHTTP_STREAMLINEREADER_H
