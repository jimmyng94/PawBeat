cmake_minimum_required(VERSION 3.0.0)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

project(LSM6DS3_RaspberryPi_Library LANGUAGES CXX)
include(GNUInstallDirs)
add_subdirectory(acc_test)

# add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC LSM6DS3.cpp)
set(LIBINCLUDE LSM6DS3.h)

add_library(lsm6ds3
  SHARED
  ${LIBSRC}
  )

set_target_properties(lsm6ds3 PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(lsm6ds3 wiringPi)

install(TARGETS lsm6ds3 EXPORT lsm6ds3-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



add_library(lsm6ds3_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(lsm6ds3_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(lsm6ds3_static wiringPi)

install(TARGETS lsm6ds3_static EXPORT lsm6ds3_static-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
