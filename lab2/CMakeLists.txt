cmake_minimum_required(VERSION 3.17)
project(pobr-lab2)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(pobr-lab2 src/main.cpp include/BaseFilter.h include/ConvFilter.h src/BaseFilter.cpp src/ConvFilter.cpp include/RankFilter.h src/RankFilter.cpp)
target_link_libraries(pobr-lab2 ${OpenCV_LIBS})