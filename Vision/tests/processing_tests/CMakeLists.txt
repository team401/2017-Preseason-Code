include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB processing_tests_SRC
        "*.cpp"
        "*/*.cpp"
        )

add_executable(run_processing_tests ${processing_tests_SRC})

target_link_libraries(run_processing_tests gtest gtest_main VisionLib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${LIBV4L2_LIBRARY} ${ZMQ_LIBRARY})