# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 2.8.7)
set(Boost_USE_STATIC_LIBS       OFF)

add_definitions(-std=c++11)
project(AI_Watch_A1)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules") 
#link_directories(/usr/local/Cellar/caffe/1.0_39/lib)

# Find librealsense2 installed package
find_package(realsense2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)

find_package(GFlags)
find_package(Glog)
find_package(OpenPose REQUIRED)
find_package(Boost 1.79.0 COMPONENTS filesystem system thread iostreams chrono date_time regex REQUIRED)



pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
set(CMAKE_EXE_LINKER_FLAGS "-lrdkafka++ -lrdkafka -lgflags")

include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${GLIB_INCLUDE_DIRS} )
include_directories( ${LIBRDKAFKA_INCLUDE_DIRS})
include_directories( ${BOOST_INCLUDEDIR})
include_directories(${OpenPose_INCLUDE_DIRS} ${GFLAGS_INCLUDE_DIR} ${GLOG_INCLUDE_DIR})


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Points")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/FacadeSingleton")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Command")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Managers/OutputManagers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Managers/RealSenseManagers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Managers/CoordinateManagers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Managers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("/usr/local/opt/glib/lib/glib-2.0/include/")
include_directories("/usr/local/opt/glib/include/glib-2.0")
include_directories("/usr/local/Cellar/librdkafka/1.9.2/include") 


link_directories(/usr/local/Cellar/jsoncpp/1.9.5/lib)
link_directories(/usr/local/opt/glib/lib)
link_directories(/usr/local/Cellar/librdkafka/1.9.2/lib)
link_directories(/Users/dennycaruso/Desktop/materiale_tesi/openpose/build/caffe/lib) 
link_directories(/usr/local/opt/boost@1.79/lib)
link_directories(${BOOST_LIBRARYDIR}) 
link_directories(/usr/local/opt/gflags/lib)

pkg_check_modules(JSONCPP jsoncpp)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add the application sources to the target
# add_executable(${PROJECT_NAME} hello_librealsense2.cpp)
add_executable(AI_Watch_A1.bin main.cpp Skeleton.cpp Points/BodyKeyPoint.cpp Points/Point3D.cpp Points/Point.cpp 
FacadeSingleton/FacadeSingleton.cpp Managers/OutputManagers/OutputManager.cpp Managers/OutputManagers/OutputManagerJSON.cpp 
Managers/RealSenseManagers/RealSenseManager.cpp Managers/RealSenseManagers/RealSenseD435Manager.cpp Command/SystemCommand.cpp Command/CleanCommand.cpp 
Command/MoveCommand.cpp Command/OpenPoseCommand.cpp Managers/OpenCV_Manager.cpp Managers/UsageManager.cpp Managers/CoordinateManagers/CoordinateMappingManager.cpp
Managers/CoordinateManagers/UnityCoordinateMappingManager.cpp Managers/KafkaManager.cpp Managers/ImageManager.cpp)

# Link librealsense2 to the target
link_libraries(${JSONCPP_LIBRARIES})
target_link_libraries(AI_Watch_A1.bin PkgConfig::deps ${BOOST_LIBS} Boost::filesystem ${OpenPose_LIBS} ${GFLAGS_LIBRARY} ${GLOG_LIBRARY} ${realsense2_LIBRARY} glfw OpenGL::GL ${OpenCV_LIBS} ${PROTOBUF_LIBRARY} ${JSONCPP_LIBRARIES} ${GLIB_LIBRARIES} )