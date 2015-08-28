# Module to find Doxygen

find_package(Doxygen)

if(DOXYGEN_FOUND)
  
  configure_file(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in ${PROJECT_BINARY_DIR}/doc/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doc/Doxyfile WORKING_DIRECTORY ${PROJECT_BINARY_DIR} 
                        COMMENT "Generating API documentation with Doxygen" VERBATIM)

endif()