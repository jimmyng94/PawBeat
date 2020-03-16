/*Change pipeWriter to pipReader for building pipeReade.cpp*/

cmake_minimum_required(VERSION 3.0)

add_executable (pipeWriter pipeWriter.cpp)
target_link_libraries(pipeWriter rt)
target_include_directories(pipeWriter PRIVATE ..)
