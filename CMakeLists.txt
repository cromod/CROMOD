# CMakeLists.txt of CROMOD project
cmake_minimum_required(VERSION 2.8)
project (CROMOD)

# List of include files
include_directories (${PROJECT_SOURCE_DIR}/inc)

# List of source files
file (GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/inc/*.hpp)
set (MAIN_FILE ${PROJECT_SOURCE_DIR}/main.cpp)

# Add the static library
add_library (Internal STATIC ${SRC_FILES})
link_directories (${PROJECT_BINARY_DIR})

# Add the executable
add_executable (CROMOD ${MAIN_FILE})
target_link_libraries (CROMOD Internal)

# Find Boost libraries
find_package (Boost 1.53.0 REQUIRED)

find_path (Boost_INCLUDE 
	   NAME unit_test.hpp
	   PATHS ${Boost_INCLUDE_DIRS}
	   PATH_SUFFIXES /boost/test
	   NO_DEFAULT_PATH)
message(STATUS "Boost_INCLUDE = " ${Boost_INCLUDE})
include_directories (${Boost_INCLUDE})

find_library (Boost_LIBRARY 
	      NAME boost_unit_test_framework
	      PATHS ${Boost_LIBRARY_DIRS}
	      PATH_SUFFIXES x86_64-linux-gnu
	      NO_DEFAULT_PATH)
message (STATUS "Boost_INCLUDE = " ${Boost_LIBRARY})

# Add the unit tests
add_subdirectory (unit_tests)