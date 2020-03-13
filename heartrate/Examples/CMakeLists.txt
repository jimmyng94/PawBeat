cmake_minimum_required(VERSION 3.0)

add_executable (acc_test acc_test.cpp)
target_link_libraries(acc_test lsm6ds3 wiringPi rt)
target_include_directories(acc_test PRIVATE ..)
