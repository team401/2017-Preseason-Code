cmake_minimum_required(VERSION 2.8)
project(2017-Preseason-Code)

include(Vision/processing/cmake_modules/FindOpenCV.txt)
include(Vision/processing/cmake_modules/FindBoost.txt)
include(Vision/processing/cmake_modules/FindLibv4l2.txt)
include(Vision/processing/cmake_modules/FindZMQ.txt)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})


file(GLOB vision_SRC
        "Vision/processing/*.hpp"
        "Vision/processing/*.cpp"
        "Vision/processing/*/*.hpp"
        "Vision/processing/*/*.cpp"
        )

add_library(VisionProcessing SHARED ${vision_SRC})

add_subdirectory(Vision/tests)


add_executable(2017-Preseason-Code ${vision_SRC})
target_link_libraries(2017-Preseason-Code ${OpenCV_LIBS} ${Boost_LIBRARIES} ${LIBV4L2_LIBRARY} ${ZMQ_LIBRARY})