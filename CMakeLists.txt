cmake_minimum_required(VERSION 3.21)
add_definitions(-std=c++20)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

project(Tanks)

find_package(SFML 2.5 
  COMPONENTS 
    system window graphics network audio 
  REQUIRED)

file(GLOB_RECURSE SRCS Source/*.cpp)
file(GLOB_RECURSE HDRS Source/*.h)

add_executable(Tanks ${SRCS} ${HDRS})
target_include_directories(Tanks PRIVATE "${PROJECT_BINARY_DIR}")

target_link_libraries(Tanks sfml-graphics)

install(TARGETS Tanks DESTINATION bin)