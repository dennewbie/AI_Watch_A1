# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 2.8.7)
set(Boost_USE_STATIC_LIBS       OFF)

add_definitions(-std=c++11)
project(hello_librealsense2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules") 
#link_directories(/usr/local/Cellar/caffe/1.0_39/lib)

# Find librealsense2 installed package
find_package(realsense2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GFlags)
find_package(Glog)
find_package(OpenCV REQUIRED)
find_package(OpenPose REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Boost)
find_package(PkgConfig REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${OpenPose_INCLUDE_DIRS})
include_directories( ${GFLAGS_INCLUDE_DIR})
include_directories( ${GLOG_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Points")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/FacadeSingleton")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Command")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Managers/OutputManagers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Managers/RealSenseManagers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
link_directories(/Users/dennycaruso/Desktop/materiale_tesi/openpose/build/caffe/lib)
link_directories(/usr/local/opt/boost@1.79/lib)
link_directories(/usr/local/Cellar/jsoncpp/1.9.5/lib)


pkg_check_modules(JSONCPP jsoncpp)
# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add the application sources to the target
# add_executable(${PROJECT_NAME} hello_librealsense2.cpp)
add_executable(hello_librealsense2.bin hello_librealsense2.cpp Skeleton.cpp Points/BodyKeyPoint.cpp Points/Point3D.cpp Points/Point.cpp 
FacadeSingleton/FacadeSingleton.cpp Managers/OutputManagers/OutputManager.cpp Managers/OutputManagers/OutputManagerJSON.cpp 
Managers/RealSenseManagers/RealSenseManager.cpp Managers/RealSenseManagers/RealSenseD435Manager.cpp Command/SystemCommand.cpp Command/CleanCommand.cpp 
Command/MoveCommand.cpp Command/OpenPoseCommand.cpp)


# Link librealsense2 to the target
link_libraries(${JSONCPP_LIBRARIES})
target_link_libraries(hello_librealsense2.bin ${realsense2_LIBRARY} glfw OpenGL::GL ${OpenCV_LIBS} ${OpenPose_LIBS} ${GFLAGS_LIBRARY} ${GLOG_LIBRARY} ${PROTOBUF_LIBRARY} ${Boost_LIBRARIES} ${JSONCPP_LIBRARIES})