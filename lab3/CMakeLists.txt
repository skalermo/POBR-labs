cmake_minimum_required(VERSION 3.17)
project(pobr-lab3)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(pobr-lab3 src/main.cpp )
target_link_libraries(pobr-lab3 ${OpenCV_LIBS})