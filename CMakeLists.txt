cmake_minimum_required(VERSION 3.10)

project(VLG)

find_package(igraph REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG= "-Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp )
message(${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(VLG ${SOURCES})
target_link_libraries(VLG PUBLIC igraph::igraph)