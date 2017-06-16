cmake_minimum_required(VERSION 3.0)
project(Tanks)

set(EXECUTABLE_NAME "Tanks")
set(TESTS_EXECUTABLE_NAME "Tanks_Tests")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set (CMAKE_CXX_STANDARD 14)

if (UNIX)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g -Wall")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")


add_subdirectory(src/cmake)
add_subdirectory(test/cmake)

enable_testing()

# declares a test with our executable
add_test(NAME AllTests COMMAND ${TESTS_EXECUTABLE_NAME})


