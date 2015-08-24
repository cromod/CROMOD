# CMakeLists.txt of unit tests

include(CTest)

file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

foreach (FILE ${TEST_FILES})
  # Define the name of unit test
  get_filename_component (FILE_NAME ${FILE} NAME)
  string (REGEX REPLACE ".cpp" "" EXE_NAME ${FILE_NAME})
  # Compile the unit test
  add_executable (${EXE_NAME} ${FILE})
  target_link_libraries (${EXE_NAME} Internal)
  # Add the test in CTest
  add_test (NAME ${EXE_NAME} COMMAND "./${EXE_NAME}")
endforeach ()