cmake_minimum_required(VERSION 3.10)
project(cpptensorflow)
set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") 

find_package(OpenCV REQUIRED)
# find_package(Protobuf REQUIRED)
# include_directories(${PROTOBUF_INCLUDE_DIR})


message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

message("source cpp " ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(/home/gaofei/Tensorflow2/tensorflow-2.8.0/bazel-bin/tensorflow)
include_directories(
        /home/gaofei/Tensorflow2/abseil-cpp
        /home/gaofei/Tensorflow2/eigen3
        /home/gaofei/Tensorflow2/tensorflow-2.8.0
        /home/gaofei/Tensorflow2/tensorflow-2.8.0/bazel-bin
        ${OpenCV_INCLUDE_DIRS}
)
add_executable(cpptensorflow main.cpp TfGlint.cpp TfGlint.h)
target_link_libraries(cpptensorflow  tensorflow_cc  ${OpenCV_LIBS})
# add_executable(cpptensorflow main.cpp )
# target_link_libraries(cpptensorflow tensorflow_cc ${OpenCV_LIBS})
