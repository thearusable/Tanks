find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(BOOST_INCLUDE_DIRS $boost_installation_prefix/include)

add_definitions (-DBOOST_TEST_DYN_LINK)

file(GLOB_RECURSE ${TESTS_EXECUTABLE_NAME} "../*")

#Create executable
add_executable (${TESTS_EXECUTABLE_NAME} ../Tests.cpp)

#link libraries
target_link_libraries (${TESTS_EXECUTABLE_NAME} ${TANKS_LIBS} ${Boost_FILESYSTEM_LIBRARY}                       ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

