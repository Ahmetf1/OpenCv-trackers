cmake_minimum_required(VERSION 3.5)

project(opencv_trackers)

find_package(OpenCV REQUIRED PATHS /home/afa/opencv_4.5.1/build NO_DEFAULT_PATH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(tracker tracker.cpp)

target_link_libraries(tracker PRIVATE ${OpenCV_LIBS})
