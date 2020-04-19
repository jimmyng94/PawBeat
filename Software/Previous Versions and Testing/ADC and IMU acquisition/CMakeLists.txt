cmake_minimum_required(VERSION 3.0)

add_executable (threadedAccq threadedAccq.cpp)
find_package (Threads)
TARGET_LINK_LIBRARIES(threadedAccq rt ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(threadedAccq ADS1015 lsm6ds3 wiringPi rt)
target_include_directories(threadedAccq PRIVATE ..)
