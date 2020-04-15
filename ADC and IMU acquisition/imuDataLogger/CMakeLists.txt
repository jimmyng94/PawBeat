cmake_minimum_required(VERSION 3.0)

add_executable (imuAccq imuAccq.cpp)
find_package (Threads)
TARGET_LINK_LIBRARIES(imuAccq rt ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(imuAccq ADS1015 lsm6ds3 wiringPi rt)
target_include_directories(imuAccq PRIVATE ..)
