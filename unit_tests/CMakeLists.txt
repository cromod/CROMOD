# CMakeLists.txt of unit tests
include(CTest)

file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/unit_tests/*.cpp)

foreach (FILE ${TEST_FILES})
  get_filename_component (FILE_NAME ${FILE} NAME)
  string (REGEX REPLACE ".cpp" "" EXE_NAME ${FILE_NAME})
  add_executable (${EXE_NAME} ${FILE})
  target_link_libraries (${EXE_NAME} Internal ${Boost_LIBRARY})
  add_test (NAME ${EXE_NAME} COMMAND "./${EXE_NAME}")
endforeach ()