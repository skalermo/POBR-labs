cmake_minimum_required(VERSION 3.17)
project(pobr-lab2)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(pobr-lab2 main.cpp BaseFilter.h ConvFilter.h BaseFilter.cpp ConvFilter.cpp)
target_link_libraries(pobr-lab2 ${OpenCV_LIBS})