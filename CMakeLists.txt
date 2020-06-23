cmake_minimum_required(VERSION 3.15)
project(UM1)

set(CMAKE_CXX_STANDARD 11)

add_executable(UM1 main.cpp Machine.cpp Machine.h Machine2.cpp Machine2.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(UM1 Threads::Threads)