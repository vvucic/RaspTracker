cmake_minimum_required (VERSION 3.0)
project(RaspTracker)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )
find_package(Threads)

include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(RaspTracker ${SOURCES})

target_link_libraries( RaspTracker ${OpenCV_LIBS} )
target_link_libraries( RaspTracker ${CMAKE_THREAD_LIBS_INIT} )
