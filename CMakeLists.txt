cmake_minimum_required(VERSION 3.6)
project(2017-Preseason-Code)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Vision/main.cpp)
add_executable(2017-Preseason-Code ${SOURCE_FILES})
target_link_libraries(2017-Preseason-Code ${OpenCV_LIBS})



