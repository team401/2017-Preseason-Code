cmake_minimum_required(VERSION 2.8)
project(2017-Preseason-Code)

include(Vision/processing/src/cmake_modules/FindOpenCV.txt)
include(Vision/processing/src/cmake_modules/FindBoost.txt)
include(Vision/processing/src/cmake_modules/FindLibv4l2.txt)
include(Vision/processing/src/cmake_modules/FindZMQ.txt)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})


file(GLOB vision_SRC
        "Vision/processing/src/*.hpp"
        "Vision/processing/src/*.cpp"
        "Vision/processing/src/*/*.hpp"
        "Vision/processing/src/*/*.cpp"
        )

add_library(VisionLib ${vision_SRC})

add_subdirectory(Vision/tests)


add_executable(2017-Preseason-Code Vision/processing/main.cpp)
target_link_libraries(2017-Preseason-Code VisionLib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${LIBV4L2_LIBRARY} ${ZMQ_LIBRARY})