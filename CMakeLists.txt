cmake_minimum_required(VERSION 2.8) #This is as low as we can go for OpenCV 3
project(2017-Preseason-Code)

enable_testing()

include(Vision/processing/src/cmake_modules/FindOpenCV.txt)
include(Vision/processing/src/cmake_modules/FindBoost.txt)
include(Vision/processing/src/cmake_modules/FindLibv4l2.txt)
include(Vision/processing/src/cmake_modules/FindZMQ.txt)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #C++11 is as high as we can go

message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})


file(GLOB vision_SRC #Find all source and header files
        "Vision/processing/src/*.hpp"
        "Vision/processing/src/*.cpp"
        "Vision/processing/src/*/*.hpp"
        "Vision/processing/src/*/*.cpp"
        )

add_library(VisionLib ${vision_SRC}) #Build the source and header files as a library

add_subdirectory(Vision/tests) #Include test init


add_executable(2017-Preseason-Code Vision/processing/main.cpp) #Make an executable from main
target_link_libraries(2017-Preseason-Code VisionLib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${LIBV4L2_LIBRARY} ${ZMQ_LIBRARY}) #Link our library and found libraries to the final package