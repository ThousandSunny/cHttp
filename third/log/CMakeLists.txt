include_directories(./)

# https://github.com/emilk/loguru

# 导出动态库,取名 easylog
add_library(easylog SHARED loguru.cpp)