include_directories(./)

add_executable(client Client.cpp main.cpp HttpClient.cpp HttpConfig.cpp Call.cpp Call.h Request.cpp Request.h Response.cpp Response.h Callback.cpp Callback.h Url.cpp Url.h)