cmake_minimum_required(VERSION 3.8)
project(chat_ssoo_17)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp socket.cpp socket.h message.h)

add_executable(chat_ssoo_17 ${SOURCE_FILES})