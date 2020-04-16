cmake_minimum_required(VERSION 3.0)

add_executable (processingUpdate processingUpdate.cpp)
find_package (Threads)
TARGET_LINK_LIBRARIES(processingUpdate rt ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(processingUpdate fir_static ADS1015 lsm6ds3 wiringPi rt)
target_include_directories(processingUpdate PRIVATE ..)
