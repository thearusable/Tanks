#Window Lib
file(GLOB_RECURSE ENGINE "../Engine/*")
add_library (Engine ${ENGINE})

#Create executable
add_executable (${EXECUTABLE_NAME} ../Source.cpp)

#Link libraries
set(TANKS_LIBS Engine)
target_link_libraries (${EXECUTABLE_NAME} ${TANKS_LIBS})
