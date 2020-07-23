//
// Created by Tinggeng Yan on 2020/7/21.
//

#include "RequestLine.h"

std::string RequestLine::get(Request request) {

    std::string sb;
    sb.append(request.getMethod());
    sb.append(" ");

    Url url = request.getUrl();
    sb.append(url.getPath());

    const std::string query = url.getQuery();
    if (!query.empty()) {
        sb.append("?").append(query);
    }

    sb.append(" HTTP/1.1");

    return sb;
}