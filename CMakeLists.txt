cmake_minimum_required(VERSION 3.6)
project(2017-Preseason-Code)
find_package(OpenCV REQUIRED)
find_package(Boost 1.62.0 REQUIRED COMPONENTS system thread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB vision_SRC
        "Vision/*.h"
        "Vision/*.c"
        "Vision/*.hpp"
        "Vision/*.cpp"
        )

include_directories(${Boost_INCLUDE_DIRS})
add_executable(2017-Preseason-Code ${vision_SRC})
target_link_libraries(2017-Preseason-Code ${OpenCV_LIBS} ${Boost_LIBRARIES})
#TODO build network table binaries and then add it to the link libraries