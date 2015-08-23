# CMakeLists.txt of CROMOD project
cmake_minimum_required(VERSION 2.8)
project (CROMOD)

# Launch modules
set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/config" ${CMAKE_MODULE_PATH})
include (FindLibraries)

# List of include files
include_directories (${PROJECT_SOURCE_DIR}/inc)

# List of source files
file (GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/inc/*.hpp)
set (MAIN_FILE ${PROJECT_SOURCE_DIR}/main.cpp)

# Add the static library
add_library (Internal STATIC ${SRC_FILES})
target_link_libraries (Internal ${EXT_LIBRARIES})
link_directories (${PROJECT_BINARY_DIR})

# Add the executable
add_executable (CROMOD ${MAIN_FILE})
target_link_libraries (CROMOD Internal)

# Add the unit tests
add_subdirectory (unit_tests)