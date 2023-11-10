# cmake version >= 3.5
cmake_minimum_required(VERSION 3.5)

# project name
project(simplesat)

# set source file directory
aux_source_directory(src DIR_SRCS)

# set include directory
include_directories(include)
link_directories(lib)

# find gtest library
# remove the following line if you don't want to use gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIBRARY_DIRS})

# add executable file
add_executable(simplesat ${DIR_SRCS} main.cc)

# add test executable file
add_executable(test_simplesat ${DIR_SRCS} test.cc)
target_link_libraries(test_simplesat ${GTEST_LIBRARIES})
