# Module to generate coverage report


find_program( LCOV_PATH lcov )
find_program( GENHTML_PATH genhtml )

add_custom_target(coverage)

add_custom_command (TARGET coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage
    #COMMAND ${LCOV_PATH} --directory . --zerocounters
    COMMAND ${LCOV_PATH} --directory . --capture --output-file ./coverage/total.info
    COMMAND ${LCOV_PATH} -r ./coverage/total.info '/usr/include/*' -o ./coverage/base.info
    COMMAND ${GENHTML_PATH} -o ./coverage ./coverage/base.info --legend
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR} )