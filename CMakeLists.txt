cmake_minimum_required(VERSION 3.15)
project(sCrapper C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(sCrapper main.c scrapper.h scrapper.c)

target_link_libraries(sCrapper
        curl
)