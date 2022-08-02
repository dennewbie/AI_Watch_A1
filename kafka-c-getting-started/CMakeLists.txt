# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 2.8.12)


# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(myprogram C)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules") 

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
set(CMAKE_EXE_LINKER_FLAGS "-lrdkafka++ -lrdkafka")

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(${LIBRDKAFKA_INCLUDE_DIRS})
include_directories("/usr/local/opt/glib/lib/glib-2.0/include/")
include_directories("/usr/local/opt/glib/include/glib-2.0")
include_directories("/usr/local/Cellar/librdkafka/1.9.2/include") 

link_directories(/usr/local/opt/glib/lib)
link_directories(/usr/local/Cellar/librdkafka/1.9.2/lib)

pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
# Add the application sources to the target
# add_executable(${PROJECT_NAME} hello_librealsense2.cpp)
add_executable(producer.bin producer.c common.c)
add_executable(consumer.bin consumer.c common.c)

# Link librealsense2 to the target

target_link_libraries(producer.bin PkgConfig::deps)
target_link_libraries(consumer.bin PkgConfig::deps)

